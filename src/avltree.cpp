#include "avltree.hpp"
#include "data_base.hpp"


template class Hnode<const DBUnit&, CompareSurname>;
template class Hnode<const DBUnit&, CompareHash>;

template class AVLtree<const DBUnit&, CompareSurname>;
template class AVLtree<const DBUnit&, CompareHash>;


template<class T, class Cmp>
Hnode<T, Cmp>::Hnode(T key) : key{key} {
    height = 1;
    left = nullptr;
    right = nullptr;
}

template<class T, class Cmp>
bool operator<(const Hnode<T, Cmp>& node_l, const Hnode<T, Cmp>& node_g) {
    return Cmp(node_l, node_g);
}

template<class T, class Cmp>
unsigned int height(Hnode<T, Cmp>* node) {
    return node ? node->height : 0;
}

template<class T, class Cmp>
int bfactor(Hnode<T, Cmp>* node) {
    return height(node->right) - height(node->left);
}

template<class T, class Cmp>
void fix_height(Hnode<T, Cmp>* node) {
    unsigned int h_left = height(node->left);
    unsigned int h_right = height(node->right);
    node->height = (h_left > h_right ? h_left : h_right) + 1;
}

template<class T, class Cmp>
Hnode<T, Cmp>* rotate_right(Hnode<T, Cmp>* parent) {
	Hnode<T, Cmp>* child = parent->left;
	parent->left = child->right;
	child->right = parent;
	fixheight(child);
	fixheight(parent);
	return child;
}

template<class T, class Cmp>
Hnode<T, Cmp>* rotate_left(Hnode<T, Cmp>* parent) {
	Hnode<T, Cmp>* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	fixheight(child);
	fixheight(parent);
	return child;
}

template<class T, class Cmp>
Hnode<T, Cmp>* balance(Hnode<T, Cmp>* node) {
	fix_height(node);
	if (bfactor(node) == 2) {
		if(bfactor(node->right) < 0) {
			node->right = rotate_right(node->right);
        }
		return rotate_left(node);
	}
	if (bfactor(node) == -2) {
		if(bfactor(node->left) > 0) {
			node->left = rotate_left(node->left);
        }
		return rotate_right(node);
	}
	return node; // балансировка не нужна
}

template<class T, class Cmp>
Hnode<T, Cmp>* insert(Hnode<T, Cmp>* node, T key){
	if (!node) { return new Hnode<T, Cmp>(key); }

	if (key < node->key) {
		node->left = insert(node->left, key);
    } else {
		node->right = insert(node->right, key);
    }

	return balance(node);
}

template<class T, class Cmp>
Hnode<T, Cmp>* find_min(Hnode<T, Cmp>* node){
	return node->left ? find_min(node->left) : node;
}

template<class T, class Cmp>
Hnode<T, Cmp>* remove_min(Hnode<T, Cmp>* node) {
	if (!node->left)
		return node->right;
	node->left = remove_min(node->left);
	return balance(node);
}

template<class T, class Cmp>
Hnode<T, Cmp>* remove(Hnode<T, Cmp>* node, T key) {
	if (!node) { return 0; }

	if (key < node->key) {
		node->left = remove(node->left, key);
    } else if (key > node->key) {
		node->right = remove(node->right, key);
    } else {
		Hnode<T, Cmp>* left = node->left;
		Hnode<T, Cmp>* right = node->right;
		delete node;
		if (!right) { return left; }
		Hnode<T, Cmp>* min = find_min(right);
		min->right = remove_min(right);
		min->left = left;
		return balance(min);
	}
    return balance(node);
}

template<class T, class Cmp>
AVLtree<T, Cmp>::AVLtree(T key) {
    root = new Hnode<T, Cmp>(key);
}

template<class T, class Cmp>
AVLtree<T, Cmp>::~AVLtree() {
    destroy_tree(root);
}

template<class T, class Cmp>
void AVLtree<T, Cmp>::destroy_tree(Hnode<T, Cmp>* node) {
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

template<class T, class Cmp>
void AVLtree<T, Cmp>::insert(T key) {
    insert(root, key);
}

template<class T, class Cmp>
void AVLtree<T, Cmp>::remove(T key) {
    remove(root, key);
}


enum class HnodePos {
    Left = -1,
    Root,
    Right,
};

template<class T, class Cmp>
void print_node(std::ostream& os, const Hnode<T, Cmp>* node, int level = 0, HnodePos pos = HnodePos::Root) {
    if (node) {
        print_node(os, node->right, level + 1, HnodePos::Right);
        for (int i = 0; i < level * 5 - 1; i++) {
            os << " ";
        }
        os << ((pos == HnodePos::Left) ? " └ " : ((pos == HnodePos::Right) ? " ┌ " : ""));
        os << node->value << std::endl;
        print_node(os, node->left, level + 1, HnodePos::Left);
    }
}

template<class T, class Cmp>
std::ostream& operator<<(std::ostream& os, const AVLtree<T, Cmp>& avl_tree) {
    print_node(os, avl_tree.root);
    return os;
}

DBUnit::DBUnit(std::string name, std::string surname, size_t dormitory, size_t block)
: name{name}, surname{surname}, dormitory{dormitory}, block{block} {
    password_hash = std::hash<std::string>{}(surname + name + std::to_string(dormitory) + std::to_string(block));
}

bool CompareSurname::operator()(const DBUnit& db_unit_less, const DBUnit& db_unit_greatest){
    return db_unit_less.surname.compare(db_unit_greatest.surname);
}

bool CompareHash::operator()(const DBUnit& db_unit_less, const DBUnit& db_unit_greatest) {
    return db_unit_less.password_hash < db_unit_greatest.password_hash;
}

std::ostream& operator<<(std::ostream& os, const DBUnit& db_unit) {
    return os << db_unit.surname << " " << db_unit.name << "pass hash : " << db_unit.password_hash;
}