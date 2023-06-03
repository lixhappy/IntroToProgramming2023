#include <string>
#include <iostream>

#include "avltree.hpp"
#include "generators.hpp"

int main() {
    DBUnit unit0(std::string("Alex"), std::string("Forest"), 0, 1);
    AVLtree<DBUnit, CompareHash> tree(unit0);
    DBUnit unit1(std::string("Bill"), std::string("Smith"), 0, 1);
    DBUnit unit2(std::string("Jenkins"), std::string("Leeroy"), 0, 1);
    DBUnit unit3(std::string("Hiro"), std::string("Kim"), 0, 1);
    tree.insert(unit1);
    tree.insert(unit2);
    tree.insert(unit3);
    std::cout << unit0 << std::endl;
    std::cout << unit1 << std::endl;
    std::cout << unit2 << std::endl;
    std::cout << unit3 << std::endl;
    tree.print_tree();
    // std::cout << tree << std::endl;
    return 0;
}