#include "avltree.hpp"


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
	fix_height(child);
	fix_height(parent);
	return child;
}

template<class T, class Cmp>
Hnode<T, Cmp>* rotate_left(Hnode<T, Cmp>* parent) {
	Hnode<T, Cmp>* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	fix_height(child);
	fix_height(parent);
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
Hnode<T, Cmp>* insert_node(Hnode<T, Cmp>* node, T key){
	Cmp compare;
	if (!node) { return new Hnode<T, Cmp>(key); }

	if (compare(key, node->key) < 0) {
		node->left = insert_node(node->left, key);
    } else {
		node->right = insert_node(node->right, key);
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
Hnode<T, Cmp>* remove_node(Hnode<T, Cmp>* node, T key) {
	Cmp compare;
	if (!node) { return 0; }

	if (compare(key, node->key) < 0) {
		node->left = remove_node(node->left, key);
    } else if (compare(key, node->key) > 0) {
		node->right = remove_node(node->right, key);
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
AVLtree<T, Cmp>::AVLtree() {}

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
    root = insert_node(root, key);
}

template<class T, class Cmp>
void AVLtree<T, Cmp>::remove(T key) {
    root = remove_node(root, key);
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
        os << node->key << std::endl;
        print_node(os, node->left, level + 1, HnodePos::Left);
    }
}

template<class T, class Cmp>
std::ostream& operator<<(std::ostream& os, const AVLtree<T, Cmp>& avl_tree) {
    print_node(os, avl_tree.root);
    return os;
}

template<class T, class Cmp>
void AVLtree<T, Cmp>::print_tree() {
	print_node(std::cout, root);
	std::cout << std::endl;
}

DBUnit::DBUnit(std::string new_name, std::string new_surname, size_t dormitory, size_t block)
:dormitory{dormitory}, block{block} {
	name = new_name;
	surname = new_surname;
    password_hash = std::hash<std::string>{}(surname + name + std::to_string(dormitory) + std::to_string(block));
}

int CompareSurname::operator()(const DBUnit& db_unit_less, const DBUnit& db_unit_greatest){
    return db_unit_less.surname.compare(db_unit_greatest.surname);
}

int CompareHash::operator()(const DBUnit& db_unit_less, const DBUnit& db_unit_greatest) {
    return db_unit_less.password_hash < db_unit_greatest.password_hash ? -1 : db_unit_less.password_hash == db_unit_greatest.password_hash ? 0 : 1;
}

std::ostream& operator<<(std::ostream& os, const DBUnit& db_unit) {
    return os << db_unit.surname << " " << db_unit.name << ", pass hash : " << db_unit.password_hash;
}


template class Hnode<DBUnit, CompareSurname>;
template class Hnode<DBUnit, CompareHash>;

template class AVLtree<DBUnit, CompareSurname>;
template class AVLtree<DBUnit, CompareHash>;