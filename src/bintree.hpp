#ifndef MY_BIN_TREE
#define MY_BIN_TREE

#include <vector>
#include <iostream>

using Way = std::pair<std::vector<int>, int>;
using Ways = std::pair<Way*, Way*>;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* make_node(int value, Node* left = nullptr, Node* right = nullptr);


class Btree {
    public:
        Btree();
        Btree(Node* root);
        ~Btree();

        void insert(int key);
        void destroy_tree();
        
        friend std::ostream& operator<<(std::ostream& os, const Btree& btree);
        friend std::vector<int> find_maxsum_minsize_tree(const Btree& btree);

    private:
        void destroy_tree(Node* node);
        void insert_left(int key, Node* node);
        void insert_right(int key, Node* node);
        void insert(int key, Node* node);
        friend Ways* find_maxsum_minsize_tree(const Node* node);
        Node* root;
};

#endif