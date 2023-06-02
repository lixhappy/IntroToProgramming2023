#ifndef MY_BIN_TREE
#define MY_BIN_TREE

#include <vector>
#include <iostream>

struct Node {
    int key_value;
    Node* left;
    Node* right;
};

class Btree {
    public:
        Btree();
        ~Btree();

        void insert(int key);
        void destroy_tree();

    private:
        void destroy_tree(Node* leaf);


        Node* root;
};

std::ostream& operator<<(std::ostream& os, const Btree& btree);

#endif