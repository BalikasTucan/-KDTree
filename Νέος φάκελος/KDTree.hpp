#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include <ostream>
#include <queue>
#include "KDNode.hpp"
#include "Distance.hpp"
#include "Embedding.hpp"
#include <string>



struct CompareDistance {
    bool operator()(const Distance& a, const Distance& b) const {
        return a.distance < b.distance;
    }
};

class KDTree {
private:
    int size;
    int k_dim;
    KDNode* root;

    
    KDNode* buildTree(std::vector<Embedding>& points, int depth);
    void KNN_search_recursive(KDNode* node,const Embedding& target,int k,std::priority_queue<Distance, std::vector<Distance>,CompareDistance>& heap) const;
    void flatten(KDNode* node, std::vector<Embedding>& out) const;
    
public:
    void insert(const Embedding& e);
    KDTree(const char* filename);
    KDTree(const std::string& filename); 
    KDTree(const KDTree& ht);
    ~KDTree();

    
    std::vector<Distance> KNN_search(const Embedding& e, int k);

    
    KDTree& operator=(const KDTree& tree);
    KDTree& operator+=(const KDTree& tree);
    KDTree operator+(const KDTree& tree) const;

    
    friend std::ostream& operator<<(std::ostream& stream, const KDTree& t);
};

#endif 
