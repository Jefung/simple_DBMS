//
// Created by jefun on 2018/12/31.
//

#include <string>
#include <map>
#include "db.h"
#include "grammer_tree.h"
#include "file.h"

std::string DB::create_table(GramTree *tree) {
    // read data from tree

    // std::string table_name = tree->getChild(0)->getStrValue();
    // std::list<std::pair<std::string, int>> col_list;
    // col_list.push_back({"primary", 0});
    // GramTree *cols_tree = tree->getChild(1);
    // for (int i = 0; i < cols_tree->getChildNum(); i++) {
    //     col_list.push_back({cols_tree->getChild(i)->getStrValue(), cols_tree->getChild(i)->getNumValue()});
    //     // cols[cols_tree->getChild(i)->getStrValue()] = cols_tree->getChild(i)->getNumValue();
    // }

    // mock
    std::string table_name = "test_table";
    std::list<std::pair<std::string, int>> col_list;
    col_list.push_back({"col1", 0});
    col_list.push_back({"col2", 1});

    std::string dir = "./" + table_name;
    if (File::create_dir(dir)) {

        auto fs = File::create("./" + table_name + "/" + table_name + ".frm");
        if (!fs.good())
            std::cout << "fs is bad" << std::endl;
        for (auto it = col_list.begin(); it != col_list.end(); it++) {
            fs << it->first << " " << it->second << std::endl;
        }
        fs.close();
        return "create table " + table_name + " successfully";
    } else {
        // handle exception
        return "table " + table_name + " is exists";
    }
}

std::string DB::drop_table(GramTree *tree) {
    // read data from tree
    // std::string table_name = tree->getChild(0)->getStrValue();

    // mock
    std::string table_name = "test_table";
    std::string dir = "./" + table_name;

    if (!File::dir_exists(table_name))
        return "table " + table_name + " is not exists";
    if (File::rm_dir(dir)) {
        return "drop table " + table_name + " successfully";
    } else {
        return "drop table failed: " + File::get_error();
    }
}

// todo: 匹配列类型
std::string DB::insert(GramTree *tree) {
    // std::string table_name = tree->getChild(0)->getStrValue();
    // if(!table_exists(table_name))
    //     return table_name + " doesn't exists";

    // ColsInfo cols = get_cols_info(table_name);
    // GramTree *cols_tree = tree->getChild(1);
    // if(cols_tree->getChildNum() != cols.size())
    //     return "cols size not equal the nums of insert valus";
    //
    // std::vector<std::string> insert_values;
    // for (int i = 0; i < cols_tree->getChildNum(); i++) {
    //     // 0 is num
    //     if(cols[i].second == 0){
    //         if(cols_tree->getChild(i)->getType() != GramTree::GRAM_NUMVALUE)
    //             return "the type of insert type can't match column type";
    //         insert_values.push_back(std::to_string(cols_tree->getChild(i)->getNumValue()));
    //         continue;
    //     }
    //
    //     if(cols[i].second == 1){
    //         if(cols_tree->getChild(i)->getType() != GramTree::GRAM_STRVALUE)
    //             return "the type of insert type can't match column type";
    //         insert_values.push_back(cols_tree->getChild(i)->getStrValue());
    //         continue;
    //     }
    //     return "insert value must be int(0) or char(1)";
    // }
// mock

    std::string table_name = "test_table";
    std::vector<std::string> insert_values;
    insert_values.push_back("col1_value");
    insert_values.push_back("col2_value");
    load_table_instance(table_name);
    for(auto it : insert_values)
        std::cout << it << std::endl;
    std::string msg =tables[table_name]->insert(insert_values);
    tables[table_name]->save();
    return msg;
}

bool DB::table_exists(std::string table_name) {
    if (!File::dir_exists("./" + table_name))
        return false;
    if (File::file_exists("./" + table_name + ".frm"))
        return true;
    else
        return false;
}



DB::ColsInfo DB::get_cols_info(std::string table_name) {
    return tables[table_name]->get_cols_type();
}

void DB::load_table_instance(std::string table_name) {

    // std::shared_ptr<Table> table = std::make_shared<Table>(table_name);
    // tables[table_name] = table;
    if(tables.find(table_name) != tables.end())
        return;
    Table *table = new Table(table_name);
    tables[table_name] = table;
}

std::string DB::select(GramTree *tree) {
    // std::string table_name = tree->getChild(0)->getStrValue();
    // if(!table_exists(table_name))
    //     return table_name + " doesn't exists";
    // std::vector<std::string> cols;
    // for (int i = 0; i < tree->getChild(1)->getChildNum(); i++) {
    //     cols.push_back(tree->getChild(1)->getChild(i)->getStrValue());
    //     // todo: check col name if exists
    // }
    // tables[table_name]->select(tree->getChild(2));

    // mock
    std::cout << "select" << std::endl;
    std::string table_name = "test_table";
    load_table_instance(table_name);
    std::vector<std::string> cols;
    auto res = tables[table_name]->select(nullptr);
    for (auto it : res) {
        std::vector<std::string> data = it.first->data[it.second];
        for (auto it2 : data) {
           std::cout << it2 <<" ";
        }
        std::cout <<std::endl;
    }
    return "";
}
