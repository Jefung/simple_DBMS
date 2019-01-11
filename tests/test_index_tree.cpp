#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "index_tree/col_types/string.h"
#include "index_tree/col_types/int.h"
#include "index_tree/col_types/col_type_interface.h"
#include "index_tree/index.h"
#include <typeinfo>
#include "index_tree/b_plus_tree.h"


TEST(test_b_plus_tree, test_int_as_index){
    extern std::vector<int> input_keys;
    BPlusTree<Index, int> tree;
    std::list<Index> order_input;
    for(int i = 0; i < input_keys.size(); i++){
        int key = input_keys[i];
        Index index;
        Int *int_p = new Int(i);
        String *str_p = new String("test");
        index.push_back(int_p);
        index.push_back(str_p);

        order_input.push_back(index);
        tree.insert(index, i);

        order_input.sort();
        auto forward_list = tree.get_forward_index_list();
        ASSERT_EQ(order_input, forward_list);

        order_input.reverse();
        auto reverse_list = tree.get_reverse_index_list();
        ASSERT_EQ(order_input, reverse_list);
    }
}

