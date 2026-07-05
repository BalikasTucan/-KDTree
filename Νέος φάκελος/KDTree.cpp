#include "KDTree.hpp"
#include "Embedding.hpp"
#include "InvalidDimensionsException.hpp"
#include <algorithm>
#include <queue>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <map>

static std::string fmt(double x, int prec) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(prec) << x;
    std::string s = ss.str();
    size_t p = s.find('.');
    if (p != std::string::npos) {
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (!s.empty() && s.back() == '.') s.pop_back();
    }
    return s;
}
static KDNode* copyNodes(const KDNode* node) {
    if (!node) return nullptr;
    KDNode* newNode = new KDNode(node->getEmbedding(),node->getAxis() );
    newNode->setLeft(copyNodes(node->getLeft()));
    if (newNode->getLeft()) newNode->getLeft()->setParent(newNode);
    newNode->setRight(copyNodes(node->getRight()));
    if (newNode->getRight()) newNode->getRight()->setParent(newNode);
    return newNode;
}


KDNode* KDTree::buildTree(std::vector<Embedding>& points, int depth) {
    if (points.empty()) return nullptr;
    int axis = depth % k_dim;
    auto comp = [axis](const Embedding& a, const Embedding& b) {
    double av = a.getVector()[axis], bv = b.getVector()[axis];
    if (av < bv) return true;
    if (av > bv) return false;
    return a.getWord() < b.getWord();
    };
    std::sort(points.begin(), points.end(), comp);
    
    
    size_t median = (points.size() - 1) / 2;
    Embedding medianPoint = points[median];

    KDNode* node = new KDNode(medianPoint, axis);
    std::vector<Embedding> leftPoints(points.begin(), points.begin() + median);
    std::vector<Embedding> rightPoints(points.begin() + median + 1, points.end());

    node->setLeft(buildTree(leftPoints, depth + 1));
    if (node->getLeft()) node->getLeft()->setParent(node);
    node->setRight(buildTree(rightPoints, depth + 1));
    if (node->getRight()) node->getRight()->setParent(node);

    return node;
}
void KDTree::KNN_search_recursive(KDNode* node,const Embedding& target, int k, std::priority_queue<Distance,std::vector<Distance>,CompareDistance>& heap) const {
    if (!node) return;
    const auto& v  = node->getEmbedding().getVector();
    const auto& tv = target.getVector();

    double distSq = 0.0;
    for (int i = 0; i < k_dim; ++i) {
        double d = v[i] - tv[i];
        distSq += d*d;
    }
    double dist = std::sqrt(distSq);

      const std::string& w = node->getEmbedding().getWord();
    if ((int)heap.size() < k) {
        
        std::cout << "Adding: " << fmt(dist,4) << " [" << w << "]\n";
        
        
        heap.push(Distance{dist, w});
    }
    else if (dist < heap.top().distance) {
        {
            auto worst = heap.top();
            std::cout << "Removing: " << fmt(worst.distance,4)
            << " [" << worst.word << "]\n";
        }
        
        heap.pop();
        
        std::cout << "Adding: " << fmt(dist,4) << " [" << w << "]\n";

        heap.push(Distance{dist, w});
    }


    int axis = node->getAxis();      
    double diff = tv[axis] - v[axis];
    KDNode* near = diff < 0 ? node->getLeft() : node->getRight();
    KDNode* far  = diff < 0 ? node->getRight() : node->getLeft();

    KNN_search_recursive(near, target, k, heap);
    if ((int)heap.size() < k || std::abs(diff) < heap.top().distance) {
        KNN_search_recursive(far, target, k, heap);
    }
}
void KDTree::flatten(KDNode* node, std::vector<Embedding>& out) const {
    if (!node) return;
    out.push_back(node->getEmbedding());
    flatten(node->getLeft(), out);
    flatten(node->getRight(), out);
}

void KDTree::insert(const Embedding& e) {
    if (!root) {
        root = new KDNode(e, 0);
        size = 1;
        k_dim = e.getDimensions();
        return;
    }
    KDNode* cur = root;
    int depth = 0;
    while (true) {
        int axis = depth % k_dim;
        if (e.getVector()[axis] < cur->getEmbedding().getVector()[axis]) {
            if (cur->getLeft()) {
                cur = cur->getLeft();
            } else {
                cur->setLeft(new KDNode(e, (depth+1) % k_dim, nullptr, nullptr, cur));
                size++;
                break;
            }
        } else {
            if (cur->getRight()) {
                cur = cur->getRight();
            } else {
                cur->setRight(new KDNode(e, (depth+1) % k_dim, nullptr, nullptr, cur));
                size++;
                break;
            }
        }
        depth++;
    }
}


KDTree::KDTree(const char* filename) {
    std::vector<Embedding> embeddings = readVectors(filename);
    size = static_cast<int>(embeddings.size());
    k_dim = size > 0 ? embeddings[0].getDimensions() : 0;
    root = buildTree(embeddings, 0);
}
KDTree::KDTree(const std::string& filename)
  : KDTree(filename.c_str())
{}

KDTree::KDTree(const KDTree& ht)
    : size(ht.size), k_dim(ht.k_dim), root(copyNodes(ht.root)) {}


KDTree::~KDTree() {
    delete root;
}





std::vector<Distance> KDTree::KNN_search(const Embedding& e, int k) {
    std::priority_queue<Distance, std::vector<Distance>, CompareDistance> heap;
    KNN_search_recursive(root, e, k, heap);

    std::vector<Distance> result;
    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }
    
    return result;
}


KDTree& KDTree::operator=(const KDTree& tree) {
    if (this != &tree) {
        delete root;
        size = tree.size;
        k_dim = tree.k_dim;
        root = copyNodes(tree.root);
    }
    return *this;
}


KDTree& KDTree::operator+=(const KDTree& other) {
    if (k_dim != other.k_dim) {
        throw InvalidDimensionsException();
}
    
    std::vector<Embedding> temp;
    temp.reserve(size + other.size);
    flatten(root, temp);
    flatten(other.root, temp);

    std::map<std::string, Embedding> uniq;
    for (const auto& e : temp) { 
        uniq.insert(std::make_pair(e.getWord(), e));
    }

    std::vector<Embedding> all;
    all.reserve(uniq.size());
    for (auto& kv : uniq) {
        all.push_back(kv.second);
    }

    
    delete root;

    
    size = static_cast<int>(all.size());
    root = buildTree(all, 0);
    return *this;
}


KDTree KDTree::operator+(const KDTree& other) const {
    KDTree tmp(*this);
    tmp += other;
    return tmp;
}


static void printPreOrder(std::ostream& stream, KDNode* node) {
    if (!node) return;
    stream << node->getEmbedding().getWord() << "\n";
    printPreOrder(stream, node->getLeft());
    printPreOrder(stream, node->getRight());
}

std::ostream& operator<<(std::ostream& stream, const KDTree& t) {
    printPreOrder(stream, t.root);
    return stream;
}
