#ifndef KDNODE_HPP
#define KDNODE_HPP

#include "Embedding.hpp"

class KDNode {
private:
    Embedding e;
    int split_axis;
    KDNode* left;
    KDNode* right;
    KDNode* parent;

public:

    KDNode(const Embedding& e, int split_axis,
           KDNode* left = nullptr, KDNode* right = nullptr, KDNode* parent = nullptr);

    
    KDNode(const KDNode& node);

    
    ~KDNode();


    Embedding& getEmbedding() const;
    int  getAxis()  const;
    
    KDNode* getLeft() const;
    KDNode* getRight() const;
    KDNode* getParent() const;

     
    void setLeft(KDNode* node);
    void setRight(KDNode* node);
    void setParent(KDNode* node);
};

#endif 
