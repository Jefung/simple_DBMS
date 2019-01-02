//
// Created by jefun on 2018/12/31.
//

#ifndef DBMS_DB_H
#define DBMS_DB_H


#include "grammer_tree.h"
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

    bool table_exists(std::string table_name);

    // void load_table_info(std::string table_name);

    void load_table_instance(std::string table_name);

    ColsInfo get_cols_info(std::string table_name);
};


#endif //DBMS_TABLE_H
