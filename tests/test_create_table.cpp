//
// Created by jefun on 2018/12/31.
//
#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "grammer_tree.h"
#include "db.h"

TEST(Table, create) {
    DB db;
    std::cout << db.create_table(nullptr) << std::endl;
    std::cout << db.drop_table(nullptr) << std::endl;
    std::cout << db.create_table(nullptr) << std::endl;
    std::cout << db.create_table(nullptr) << std::endl;

    // EXPECT_EQ(1,1);
    // EXPECT_NE(1,2);
    // EXPECT_TRUE(true);
    // EXPECT_FALSE(false);
}
//
TEST(Table, insert){
    // Db db;
    DB db;
    // std::cout << db.create_table(nullptr) << std::endl;
    std::cout << db.insert(nullptr) << std::endl;
    // std::cout << db.insert(nullptr) << std::endl;
    // std::cout << "---------" << std::endl;
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST(Table, select) {
    DB db;
    std::cout << db.select(nullptr) << std::endl;
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST(Example2, action1) {
    std::string s("40");
    EXPECT_TRUE(s.compare("5") < 0);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST(Example2, action2) {
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST(Example2, action3) {
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

