#include "gtest/gtest.h"
#include "common.h"
// 已经把src加入头文件查找目录,可以直接相对路径include
TEST(Example, Equals) {
    EXPECT_EQ(1, 1);
}

// todo: 增加更多例子便于平时开发查询
