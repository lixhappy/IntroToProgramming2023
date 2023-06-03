#ifndef MY_AVL_TREE
#define MY_AVL_TREE

#include <string>
#include <vector>
#include <iostream>

template<class T, class Cmp>
struct Hnode {
    T key;
    unsigned int height;
    Hnode<T, Cmp>* left = nullptr;
    Hnode<T, Cmp>* right = nullptr;
    Hnode(T key);
};

template<class T, class Cmp>
bool operator<(const Hnode<T, Cmp>& node_l, const Hnode<T, Cmp>& node_g);


template<class T, class Cmp>
unsigned int height(Hnode<T, Cmp>* node);

template<class T, class Cmp>
int bfactor(Hnode<T, Cmp>* node);

template<class T, class Cmp>
void fix_height(Hnode<T, Cmp>* node);

template<class T, class Cmp>
Hnode<T, Cmp>* rotate_right(Hnode<T, Cmp>* parent);

template<class T, class Cmp>
Hnode<T, Cmp>* rotate_left(Hnode<T, Cmp>* parent);

template<class T, class Cmp>
Hnode<T, Cmp>* balance(Hnode<T, Cmp>* node);

template<class T, class Cmp>
Hnode<T, Cmp>* insert_node(Hnode<T, Cmp>* node, T key);

template<class T, class Cmp>
Hnode<T, Cmp>* find_min(Hnode<T, Cmp>* node);

template<class T, class Cmp>
Hnode<T, Cmp>* remove_min(Hnode<T, Cmp>* node);

template<class T, class Cmp>
Hnode<T, Cmp>* remove_node(Hnode<T, Cmp>* node, T key);


template<class T, class Cmp>
class AVLtree {
    public:
        AVLtree();
        AVLtree(T key);
        ~AVLtree();
        void insert(T key);
        void remove(T key);

        friend std::ostream& operator<<(std::ostream& os, const AVLtree<T, Cmp>& avl_tree);
        void print_tree();

    private:
        void destroy_tree(Hnode<T, Cmp>* node);
        Hnode<T, Cmp>* root;
};

#include <functional>

struct DBUnit {
    DBUnit(std::string name, std::string surname, size_t dormitory, size_t block);
    std::string name;
    std::string surname;
    size_t dormitory;
    size_t block;
    size_t password_hash;
};

std::ostream& operator<<(std::ostream& os, const DBUnit& db_unit);

class CompareSurname {
public:
    int operator()(const DBUnit& db_unit_l, const DBUnit& db_unit_r);
};

class CompareHash {
public:
    int operator()(const DBUnit& db_unit_l, const DBUnit& db_unit_r);
};


class DataBase {
    private:
        std::vector<DBUnit> vec_of_units;
        AVLtree<const DBUnit&, CompareSurname> surnames_tree;
        AVLtree<const DBUnit&, CompareHash> hashes_tree;
};


#endif