#include "KDNode.hpp"


KDNode::KDNode(const Embedding& e, int split_axis,
               KDNode* left, KDNode* right, KDNode* parent)
    : e(e), split_axis(split_axis),
      left(left), right(right), parent(parent) {}


KDNode::KDNode(const KDNode& node)
    : e(node.e),
      split_axis(node.split_axis),
      left(nullptr),
      right(nullptr),
      parent(nullptr) {}

KDNode::~KDNode() {
    delete left;
    delete right;
}


Embedding& KDNode::getEmbedding() const {
    return const_cast<Embedding&>(e);
}
int KDNode::getAxis() const {
    return split_axis;
}

KDNode* KDNode::getLeft() const   { return left; }
KDNode* KDNode::getRight() const  { return right; }
KDNode* KDNode::getParent() const { return parent; }


void KDNode::setLeft(KDNode* node)   { left = node; }
void KDNode::setRight(KDNode* node)  { right = node; }
void KDNode::setParent(KDNode* node) { parent = node; }
