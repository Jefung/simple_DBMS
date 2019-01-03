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
    * [CMakeLists.txt](src/CMakeLists.txt)
    * [column.h](src/column.h)
    * [db.cpp](src/db.cpp)
    * [db.h](src/db.h)&nbsp;:&nbsp; DB控制器, 创建/删除库, 加载表, 控制表<br/>
    * [file.cpp](src/file.cpp)
    * [file.h](src/file.h)&nbsp;:&nbsp; 文件操作类<br/>
    * [gram.cpp](src/gram.cpp)
    * [gram.h](src/gram.h)&nbsp;:&nbsp; 语法树的定义<br/>
    * [index_tree.cpp](src/index_tree.cpp)
    * [index_tree.h](src/index_tree.h)&nbsp;:&nbsp; 索引(B+)树的定义<br/>
    * [lex.cpp](src/lex.cpp)
    * [lex.h](src/lex.h)&nbsp;:&nbsp; 词法token定义<br/>
    * [lex.yy.cpp](src/lex.yy.cpp)
    * [main.cpp](src/main.cpp)
    * [main_copy.cpp](src/main_copy.cpp)
    * [sql_gram.tab.cpp](src/sql_gram.tab.cpp)&nbsp;:&nbsp; 语法分析器及main入口函数<br/>
    * [sql_gram.tab.h](src/sql_gram.tab.h)
    * [table.cpp](src/table.cpp)
    * [table.h](src/table.h)&nbsp;:&nbsp; 表类, 对表的增删查改操作<br/>
* [CMakeLists.txt](CMakeLists.txt)
* [README.md](README.md)

---

## 参考链接/书籍
* MySQL技术内幕(InnoDB存储引擎)
* [InnoDB 存储引擎体系架构 - ygmyth - SegmentFault 思否](https://segmentfault.com/a/1190000004673132)
* [MySQL探秘(三):InnoDB的内存结构和特性 - remCarpediem的Android探索之旅 - SegmentFault 思否](https://segmentfault.com/a/1190000016155584)
* [B树和B+树的插入、删除图文详解 - nullzx - 博客园](https://www.cnblogs.com/nullzx/p/8729425.html)