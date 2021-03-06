//
// Created by jefun on 2018/12/31.
//
#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "index_tree/b_plus_tree.h"

TEST(BPlusTree, int_as_index_and_int_as_data) {
    extern std::vector<int> input_keys;
    BPlusTree<int,int> tree;
    std::list<int> order_input;
    // test insert
    for(int i = 0; i < input_keys.size(); i++){
        int key = input_keys[i];
        order_input.push_back(key);
        order_input.sort();
        tree.insert(key,i);

        auto forward_list = tree.get_forward_index_list();
        ASSERT_EQ(order_input,order_input);

        order_input.reverse();
        auto reverse_list = tree.get_reverse_index_list();
        ASSERT_EQ(order_input,reverse_list);
    }
    // test delete
    for(int i = 0; i < input_keys.size(); i++){
        int key = input_keys[i];
        order_input.remove(key);
        order_input.sort();
        tree.del(key);

        auto forward_list = tree.get_forward_index_list();
        ASSERT_EQ(order_input,order_input);

        order_input.reverse();
        auto reverse_list = tree.get_reverse_index_list();
        ASSERT_EQ(order_input,reverse_list);
    }
}


