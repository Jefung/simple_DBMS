#include "gtest/gtest.h"
#include "common.h"
#include <iostream>
#include "index_tree/col_types/string.h"
#include "index_tree/col_types/col_type_interface.h"

TEST(tree_index, col_type) {
    ColTypeInterface *p1;
    p1 = new String("ad");
    p1->t();

    ColTypeInterface *p2;
    p2 = new String("b");
    p2->t();

    EXPECT_TRUE(*p1 < *p2);
    EXPECT_FALSE(false);
}
// TEST(Example1, action2) {
//     EXPECT_EQ(1,1);
//     EXPECT_NE(1,2);
//     EXPECT_TRUE(true);
//     EXPECT_FALSE(false);
// }
// TEST(Example1, action3) {
//     EXPECT_EQ(1,1);
//     EXPECT_NE(1,2);
//     EXPECT_TRUE(true);
//     EXPECT_FALSE(false);
// }
// TEST(Example2, action1) {
//     EXPECT_EQ(1,1);
//     EXPECT_NE(1,2);
//     EXPECT_TRUE(true);
//     EXPECT_FALSE(false);
// }
// TEST(Example2, action2) {
//     EXPECT_EQ(1,1);
//     EXPECT_NE(1,2);
//     EXPECT_TRUE(true);
//     EXPECT_FALSE(false);
// }
// TEST(Example2, action3) {
//     EXPECT_EQ(1,1);
//     EXPECT_NE(1,2);
//     EXPECT_TRUE(true);
//     EXPECT_FALSE(false);
// }

