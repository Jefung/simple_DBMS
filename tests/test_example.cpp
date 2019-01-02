// #include "gtest/gtest.h"
// #include "common.h"
// #include <iostream>
// #include "boost/variant.hpp"
// #include <boost/any.hpp>
//
// class Indexes {
// private:
//     using IndexType = boost::variant<int, double, std::string>;
//     std::vector<IndexType> _v;
//     // int _size;
// public:
//
//     IndexType get(int index) const {
//         return _v[index];
//     }
//
//     int size() const {
//         return _v.size();
//     }
//
//     void push(const IndexType &i) {
//         _v.push_back(i);
//     }
//
//     void clear() {
//         _v.clear();
//     }
//
//     friend std::ostream &operator<<(std::ostream &stream, const Indexes &i) {
//         stream << i._v[0];
//         return stream;
//     }
//
//     friend bool operator<(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) >= boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) >= boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) >= 0)
//                 return false;
//
//         }
//         return true;
//     }
//
//     friend bool operator==(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) != boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) != boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) != 0)
//                 return false;
//         }
//         return true;
//     }
//
//     friend bool operator>(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) <= boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) <= boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) < 0)
//                 return false;
//         }
//         return true;
//     }
// };
//
// Indexes empty_index;
// using namespace std;
//
// #define MAX 50
//
//
// //number of pointers or number of child blocks [numberOfPointers = numberOfNodes + 1]
// int numberOfPointers;
//
// template<typename T>
// struct Node {
//
//     int node_num;//number of nodes
//
//     Node *parent;//for parent Node and index
//     Indexes indexes[MAX];
//     T store_data;
//     Node *children[MAX];
//     Node *precursor;
//     Node *succeed;
//
//     Node() { //constructor to initialize a block
//         node_num = 0;
//         parent = NULL;
//         for (int i = 0; i < MAX; i++) {
//             indexes[i] = empty_index;
//             children[i] = NULL;
//         }
//         precursor = nullptr;
//         succeed = nullptr;
//     }
// };
//
// using INT_NODE = Node<int>;
//
// // 已经把src加入头文件查找目录,可以直接相对路径include
// TEST(Example, Equals) {
//     Indexes i1;
//     Indexes i2;
//     i1.push("1");
//     i2.push("2");
//     std::cout << i1 << std::endl;
//     EXPECT_FALSE(i1 == i2);
//     EXPECT_FALSE(i1 > i2);
//     EXPECT_TRUE(i1 < i2);
//     i1.push("abc");
//     i2.push("abcc");
//     i1.push(1.1);
//     i2.push(1.2);;
//
//     EXPECT_TRUE(i1 < i2);
//
//     Indexes i3;
//     Indexes i4;
//     i3.push("a");
//     i4.push("a");
//
//     EXPECT_EQ(i3, i4);
//
//     std::cout << i3 << std::endl;
//     // Indexes i5 = i3;
//     i4 = i3;
//     std::cout << i4 << std::endl;
//     i4.clear();
//     i4.push("z");
//     std::cout << i4 << std::endl;
//     std::cout << i3 << std::endl;
// }
//
//
//
// TEST(Example2, streambuf) {
// // #include <streambuf>
// //
// //     ostream ss(cout.rdbuf());
// //     ss << "111" << endl;
// }
// // todo: 增加更多例子便于平时开发查询
