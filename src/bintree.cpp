#include "bintree.hpp"


std::ostream& operator<<(std::ostream& os, const Btree& btree) {
    
    return os;
}


Btree::Btree() {
    root = nullptr;
}

Btree::~Btree() {
    destroy_tree(root);
}

void Btree::destroy_tree(Node* leaf) {
  if (leaf != nullptr) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}