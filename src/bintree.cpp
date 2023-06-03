#include <algorithm>

#include "bintree.hpp"

enum class NodePos {
    Left = -1,
    Root,
    Right,
};

Node* make_node(int value, Node* left, Node* right) {
    Node* pnode = new Node;
    pnode->value = value;
    pnode->left = left;
    pnode->right = right;
    return pnode;
}

void print_node(std::ostream& os, const Node* node, int level = 0, NodePos pos = NodePos::Root) {
    if (node) {
        print_node(os, node->right, level + 1, NodePos::Right);
        for (int i = 0; i < level * 5 - 1; i++) {
            os << " ";
        }
        os << ((pos == NodePos::Left) ? " └ " : ((pos == NodePos::Right) ? " ┌ " : ""));
        os << node->value << std::endl;
        print_node(os, node->left, level + 1, NodePos::Left);
    }
}

std::ostream& operator<<(std::ostream& os, const Btree& btree) {
    print_node(os, btree.root);
    return os;
}


Btree::Btree() {
    root = nullptr;
}

Btree::Btree(Node* root) : root{root} {}

Btree::~Btree() {
    destroy_tree(root);
}

void Btree::destroy_tree() {
    destroy_tree(root);
}

void Btree::destroy_tree(Node* node) {
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

void Btree::insert(int key_value) {
    if (root) {
        insert(key_value, root);
    } else {
        root = new Node;
        root->value = key_value;
        root->left = nullptr;
        root->right = nullptr;
    }
}

void Btree::insert(int key_value, Node* node) {
    if (node->value < key_value) {
        insert_right(key_value, node);
    } else {
        insert_left(key_value, node);
    }
}

void Btree::insert_right(int key_value, Node* node) {
    if (node->right) {
        insert(key_value, node->right);
    } else {
        node->right = new Node;
        node->right->value = key_value;
        node->right->left = nullptr;
        node->right->right = nullptr;
    }
}

void Btree::insert_left(int key_value, Node* node) {
    if (node->left) {
        insert(key_value, node->left);
    } else {
        node->left = new Node;
        node->left->value = key_value;
        node->left->left = nullptr;
        node->left->right = nullptr;
    }
}

Way* max(Way* way1, Way* way2) {
    if (way1->second > way2->second) {
        return way1;
    } else if (way1->second == way2->second && 
               way1->first.size() < way2->first.size()) {
        return way1;
    }
    return way2;
}

Way* sum(Way* way_l, int value, Way* way_r) {
    Way* way = new Way;
    way->first = way_l->first;
    way->second = way_l->second;
    way->first.push_back(value);
    way->second += value;
    way->first.insert(way->first.end(), way_r->first.begin(), way_r->first.end());
    return way;
}

Ways* find_maxsum_minsize_tree(const Node* node) {
    if (!node) {
        return new Ways(new Way(std::vector<int>(1), 0), new Way(std::vector<int>(1), 0));
    }
    Ways* left_ways = find_maxsum_minsize_tree(node->left);
    Ways* right_ways = find_maxsum_minsize_tree(node->right);
    Way* left_complete_way = left_ways->first;
    Way* right_complete_way = right_ways->first;
    Way* left_uncompleted_way = left_ways->second;
    Way* right_uncompleted_way = right_ways->second;

    Way* ordinary_way = new Way;
    ordinary_way->first = {node->value};
    ordinary_way->second = node->value;

    Way* new_complete_way = sum(left_uncompleted_way, node->value, right_uncompleted_way);

    Way* max_complete_way = max(left_complete_way, right_complete_way);
    max_complete_way = max(new_complete_way, max_complete_way);
    max_complete_way = max(ordinary_way, max_complete_way);

    right_uncompleted_way->first.insert(right_uncompleted_way->first.begin(), node->value);
    right_uncompleted_way->second += node->value;
    left_uncompleted_way->first.push_back(node->value);
    left_uncompleted_way->second += node->value;

    Way* max_uncomplete_way = max(right_complete_way, left_complete_way);
    max_uncomplete_way = max(ordinary_way, max_uncomplete_way);

    return new Ways(max_complete_way, max_uncomplete_way);
}

std::vector<int> find_maxsum_minsize_tree(const Btree& btree) {
    Ways* ways = find_maxsum_minsize_tree(btree.root);
    return ways->first->first;
}