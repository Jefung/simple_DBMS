//
// Created by jefun on 2018/12/31.
//
#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "file.h"

TEST(file, create_or_overwrite){
   auto fs = File::overwrite("test_.txt");
   if(fs.good())
      std::cout << "good" << std::endl;
   fs << "a" << " " << 2 << std::endl;
   fs << "v" << " " << 2 << std::endl;
   fs.close();
}

TEST(file, create_dir){
    EXPECT_EQ(File::create_dir("dir1"),true);
    EXPECT_EQ(File::rm_dir("dir1"),true);
    EXPECT_EQ(File::create_dir("dir2"),true);
    EXPECT_NE(File::rm_dir("d"),true);
    EXPECT_EQ(File::rm_dir("dir2"),true);
    // auto files = File::traversal_dir(".");
    // auto match_files = File::match_files(".","txt");
    // std::cout << match_files.size() << std::endl;
    // std::cout << match_files[0] << std::endl;
}

TEST(vector, vector_as_map_key){
    std::map<std::vector<int>,int> m;
    std::vector<int> v(1);
    m[v] = 1;
    std::cout << m[v] << std::endl;
    std::vector<int> v1(1);
    std::cout << m[v1] << std::endl;
}

