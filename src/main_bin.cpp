#include <iostream>

#include "bintree.hpp"
#include "generators.hpp"

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec) {
    for (int i : vec) {
        os << i << " ";
    }
    return os;
}

int main() {
    Node* root = make_node(8, make_node(1, make_node(4), make_node(-1, nullptr, 
                                                                       make_node(5))), 
                              make_node(0, nullptr,
                                           make_node(2, make_node(-2))));


    Btree btree(root);
    
    
    std::cout << btree << std::endl;
    std::cout << find_maxsum_minsize_tree(btree) << std::endl;
    return 0;
}