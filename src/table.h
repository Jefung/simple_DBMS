//
// Created by jefun on 2019/1/1.
//
// comment: 表类, 对表的增删查改操作

#ifndef DBMS_TABLE_H
#define DBMS_TABLE_H

#include "index_tree.h"
#include "file.h"
#include "gram.h"

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
    Table(std::string table_name) : _table_name(table_name) {
        load_cols_type();
        load_data_from_file();
    };

    std::string insert(RowType row);

    int del(GramTree *tree);

    std::vector<std::pair<DBBPlusTree<RowType>::DataNode *, int>> get_suitable_rows(GramTree *cond);

    void save();

    void load_data_from_file();

    std::string get_data_file();

    std::vector<std::vector<std::string>> select(GramTree *tree);

    std::vector<std::string> selected_row_to_res(GramTree *selected_list, std::vector<std::string> row);

    int update(GramTree *tree);


    void load_cols_type();

    std::vector<std::pair<std::string, int>> get_cols_type();

    void load_second_indexes();

    std::string  create_second_indexes(GramTree* tree);
    std::string  drop_second_indexes(GramTree* tree);

    int get_col_pos(std::string col_name);

    std::pair<std::vector<std::string>, DBBPlusTree<std::string>> read_index_file(std::string filename);

    bool match_cond(GramTree *cond, std::vector<std::string> row);

    bool log_or(GramTree *cond, std::vector<std::string> row);

    bool log_and(GramTree *cond, std::vector<std::string> row);

    bool not_null(GramTree *cond, std::vector<std::string> row);

    bool is_null(GramTree *cond, std::vector<std::string> row);

    bool compare_less(GramTree *cond, std::vector<std::string> row);

    bool compare_greater(GramTree *cond, std::vector<std::string> row);

    bool compare_greater_equal(GramTree *cond, std::vector<std::string> row);

    bool compare_less_equal(GramTree *cond, std::vector<std::string> row);

    bool compare_equal(GramTree *cond, std::vector<std::string> row);

    int operation(GramTree *cond, std::vector<std::string> row);

    int umius(GramTree *cond, std::vector<std::string> row);

    int plus(GramTree *cond, std::vector<std::string> row);

    int minus(GramTree *cond, std::vector<std::string> row);

    int devide(GramTree *cond, std::vector<std::string> row);

    int muliply(GramTree *cond, std::vector<std::string> row);

    int factor(GramTree *cond, std::vector<std::string> row);
};


#endif //DBMS_TABLE_H
