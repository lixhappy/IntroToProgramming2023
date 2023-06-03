#ifdef MY_BIN_TREE

#include "gtest/gtest.h"
#include "../src/bintree.hpp"
#include <vector>

TEST(TEST_BIN, test0) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(bintree, find_maxsum_minsize_tree) {
    std::vector<int> ans = {4, 1, 8, 0, 2};
    Node* root = make_node(8, make_node(1, make_node(4), make_node(-1, nullptr, 
                                                                       make_node(5))), 
                              make_node(0, nullptr,
                                           make_node(2, make_node(-2))));
    Btree btree(root);
    std::vector<int> my_ans = find_maxsum_minsize_tree(btree);
    EXPECT_EQ(ans.size(), my_ans.size());
    for (int i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], my_ans[i]);
    }
}

#endif