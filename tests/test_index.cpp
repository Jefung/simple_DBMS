//
// Created by jefun on 2018/12/31.
//
#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "index_tree/col_types/string.h"
#include "index_tree/col_types/int.h"
#include "index_tree/col_types/col_type_interface.h"
#include "index_tree/index.h"

TEST(test_col_type, String){
    ColTypeInterface *p1;
    p1 = new String("a");

    ColTypeInterface *p2;
    p2 = new String("b");

    EXPECT_TRUE(*p1 < *p2);
    EXPECT_TRUE(*p1 <= *p2);
    EXPECT_FALSE(*p1 > *p2);
    EXPECT_FALSE(*p1 >= *p2);
    EXPECT_TRUE(*p1 != *p2);
    EXPECT_FALSE(*p1 == *p2);

    ColTypeInterface *p3;
    p3 = new String("c");
    ColTypeInterface *p4;
    p4 = new String("c");


    EXPECT_TRUE(*p3 == *p3);
    EXPECT_TRUE(*p3 == *p4);
    EXPECT_TRUE(*p3 <= *p4);
    EXPECT_TRUE(*p3 >= *p4);
    EXPECT_FALSE(*p3 != *p4);
    EXPECT_FALSE(*p3 < *p4);
    EXPECT_FALSE(*p3 > *p4);
    EXPECT_FALSE(false);
}

TEST(test_col_type, Int){
    ColTypeInterface *p1;
    p1 = new Int(1);

    ColTypeInterface *p2;
    p2 = new Int(2);

    EXPECT_TRUE(*p1 < *p2);
    EXPECT_TRUE(*p1 <= *p2);
    EXPECT_FALSE(*p1 > *p2);
    EXPECT_FALSE(*p1 >= *p2);
    EXPECT_TRUE(*p1 != *p2);
    EXPECT_FALSE(*p1 == *p2);

    ColTypeInterface *p3;
    p3 = new Int(3);
    ColTypeInterface *p4;
    p4 = new Int(3);

    EXPECT_TRUE(*p3 == *p3);
    EXPECT_TRUE(*p3 == *p4);
    EXPECT_TRUE(*p3 <= *p4);
    EXPECT_TRUE(*p3 >= *p4);
    EXPECT_FALSE(*p3 != *p4);
    EXPECT_FALSE(*p3 < *p4);
    EXPECT_FALSE(*p3 > *p4);
    EXPECT_FALSE(false);
}

TEST(test_index, compare_op){
    String s1("a");
    String s2("a");
    Int i1(0);
    Int i2(1);

    Index index1;
    Index index2;
    index1.push_back(&s1); // values: "a"
    index2.push_back(&s2); // values: "a"
    EXPECT_TRUE(index1 == index2);

    index1.push_back(&i1); // values: "a" 0
    index2.push_back(&i2); // values: "a" 1

    EXPECT_TRUE(index1 < index2);
    EXPECT_FALSE(index1 > index2);
    EXPECT_FALSE(index1 == index2);
}

bool compare_index(const Index &i1, const Index &i2){
    return i1 < i2;
}

