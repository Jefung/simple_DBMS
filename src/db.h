//
// Created by jefun on 2018/12/31.
//
// comment: DB控制器, 创建/删除库, 加载表, 控制表

#ifndef DBMS_DB_H
#define DBMS_DB_H


#include "gram.h"
#include <list>
#include <vector>
#include "table.h"

class DB {
private:
    using ColsInfo = std::vector<std::pair<std::string, int>>;
    std::map<std::string, ColsInfo> tables_info;
    std::map<std::string, Table *> tables;

public:
    std::string create_table(GramTree *tree);

    std::string drop_table(GramTree *tree);

    std::string insert(GramTree *tree);

    std::string select(GramTree *tree);

    std::string update(GramTree* tree);

    std::string del(GramTree* tree);

    std::string create_index(GramTree* tree);
    std::string drop_index(GramTree* tree);

    bool table_exists(std::string table_name);

    // void load_table_info(std::string table_name);

    void load_table_instance(std::string table_name);

    ColsInfo get_cols_info(std::string table_name);
};


#endif //DBMS_TABLE_H
