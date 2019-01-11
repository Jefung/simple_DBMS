# DBMS
## Todo
- [x] 表的建立(简单指明列类型)
- [x] 对表的增删查改
- [x] 索引的建立和删除
- [ ] 对前端语法解析器的优化
- [ ] 使用索引去查找行(包括覆盖索引)
- [ ] 存储文件的优化(参照InnoDB)
- [ ] 对各种字段类型的处理, 可扩展字段

## 目录结构

* [src](src)
    * [index_tree](src/index_tree)
        * [col_types](src/index_tree/col_types)
            * [col_type_interface.cpp](src/index_tree/col_types/col_type_interface.cpp)
            * [col_type_interface.h](src/index_tree/col_types/col_type_interface.h)
            * [int.cpp](src/index_tree/col_types/int.cpp)
            * [int.h](src/index_tree/col_types/int.h)
            * [string.cpp](src/index_tree/col_types/string.cpp)
            * [string.h](src/index_tree/col_types/string.h)
        * [b_plus_tree.h](src/index_tree/b_plus_tree.h)
        * [index.cpp](src/index_tree/index.cpp)
        * [index.h](src/index_tree/index.h)
    * [CMakeLists.txt](src/CMakeLists.txt)
    * [main.cpp](src/main.cpp)
* [tests](tests)
    * [CMakeLists.txt](tests/CMakeLists.txt)
    * [common.cpp](tests/common.cpp)
    * [common.h](tests/common.h)
    * [test_b_plus_tree.cpp](tests/test_b_plus_tree.cpp)
    * [test_create_table.cpp.backup](tests/test_create_table.cpp.backup)
    * [test_example.cpp](tests/test_example.cpp)
    * [test_file.cpp.backup](tests/test_file.cpp.backup)
    * [test_index.cpp](tests/test_index.cpp)
    * [test_index_tree.cpp](tests/test_index_tree.cpp)
    * [test_table.cpp.backup](tests/test_table.cpp.backup)
    * [test_template.cpp](tests/test_template.cpp)
* [CMakeLists.txt](CMakeLists.txt)

---

## 思路
### 1. 表存储:
假设我们有个表名为`student`,其存储结构如下
```
STUDENT
├── STUDENT.frm
├── STUDENT.idb
├── index_name1.index
└── index_name2.index
    .....
```

其中`表名.frm`是表结构, `表名.idb`是行数据, `索引名.index`是索引文件.

![表创建.jpg](http://images.jefung.cn/表创建.jpg)

### 2. 索引树/B+树


#### 2.1 索引的实现

考虑mysql的索引是可以**多列**且字段也是**任意的类型**(数字,字符串等等). 所以这里我使用了
`c++`的**多态特性**, 即利用一个基类`ColTypeInterface`, 然后定义纯虚函数, 纯虚函数主要实现
该类型的各种比较操作,方便后续`b+树`的索引比较,所有自定义的列类型必须继承`ColTypeInterface`,
然后重写纯虚函数.

ps: 这里本来是想把比较函数定义为纯虚函数,如

`virtual friend bool operator>=(const ColTypeInterface &i1, const ColTypeInterface &i2) = 0;`,
然后发现`C++`不支持, google了下, 发现只要简单的重写比较函数, 然后调用其自定义的纯虚函数即可.
```cpp
bool operator<(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.less(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

virtual bool less(ColTypeInterface *p1, ColTypeInterface *p2) const = 0; // 派生类重写即可
```

自定义各种列类型之后,就要考虑有个结构能够把各种不同的列包含进来, 并实现各种比较,这里我采用的是
一个`Index`类(注意其基类), 实现Index的各种比较方法
```cpp
class Index : public std::vector<ColTypeInterface *>{
public:
    Index();

    friend bool operator<(const Index &i1, const Index &i2);

    friend bool operator==(const Index &i1, const Index &i2);

    friend bool operator>(const Index &i1, const Index &i2);

    friend bool operator>=(const Index &i1, const Index &i2);

    friend bool operator<=(const Index &i1, const Index &i2);

    friend std::ostream &operator<<(std::ostream &os, Index const &data);
};
```

具体用法可以参见 [test_index.cpp](tests/test_index.cpp)

#### 2.2 Mysql的InnoDB引擎是使用B+树作为索引树,
* 对于主索引来说, 叶节点是存放具体行数据, 对于非叶子节点来说, 不存放数据,只
存放主键内容
* 对于第二索引(index)来说, 叶节点存放的是主键, 非叶子节点存放索引内容

#### 2.3 B+树的实现
代码参考: [b_plus_tree.h](src/index_tree/b_plus_tree.h)

思路参考: [B树和B+树的插入、删除图文详解 - nullzx - 博客园](https://www.cnblogs.com/nullzx/p/8729425.html)

用法参考: [test_b_plus_tree.cpp](tests/test_b_plus_tree.cpp) (待完善)

B+树的实现是真的很恶心. 我写了好几天才写出来, 而且还不是那么完善. 有兴趣的可以研究下代码

### 3. 如何控制不同表?
不考虑多库的情况下, 对于一个库, 可能有多个表, 那么如何控制多个表呢?

这里的实现的一个`Table`是操作一个表的, 通过初始化时传入的表名参数来决定是控制
哪个表, 而`DB`类内有一个`map`来存放`Table *`, 当要使用表时, 动态生成`Table`实例,
并加入`map`中. 不需要的话直接从`map`去除就好了


## 参考链接/书籍
* MySQL技术内幕(InnoDB存储引擎)
* [InnoDB 存储引擎体系架构 - ygmyth - SegmentFault 思否](https://segmentfault.com/a/1190000004673132)
* [MySQL探秘(三):InnoDB的内存结构和特性 - remCarpediem的Android探索之旅 - SegmentFault 思否](https://segmentfault.com/a/1190000016155584)
* [B树和B+树的插入、删除图文详解 - nullzx - 博客园](https://www.cnblogs.com/nullzx/p/8729425.html)