//
// Created by jefun on 2019/1/1.
//

#ifndef DBMS_TABLE_H
#define DBMS_TABLE_H

#include "index_tree.h"
#include "file.h"
#include "grammer_tree.h"

class Table {
private:
    // using ColsInfo = std::vector<std::pair<std::string, int>>;
    std::vector<std::pair<std::string, int>> cols_type;
    using RowType = std::vector<std::string>;
    DBBPlusTree<RowType> master_index;
    std::map<std::vector<std::string>, DBBPlusTree<std::string>> second_indexes;
    std::string _table_name;
    // std::vector<std::string> cols_type;
public:
    Table(std::string table_name):_table_name(table_name){
        load_cols_type();
        load_data_from_file();
    };
    std::string insert(RowType row);

    std::vector<std::pair<DBBPlusTree<RowType>::DataNode*,int>> select(GramTree *cond);

    void save();

    void load_data_from_file();

    std::string get_data_file();

    void load_cols_type();
    std::vector<std::pair<std::string, int>> get_cols_type();
    void load_second_indexes();

    std::pair<std::vector<std::string>,DBBPlusTree<std::string>> read_index_file(std::string filename);

};


#endif //DBMS_TABLE_H
