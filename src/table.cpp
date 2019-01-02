//
// Created by jefun on 2019/1/1.
//

#include "table.h"

std::string Table::insert(Table::RowType row) {
    Indexes index = master_index.get_max_index();
    std::string max_value = boost::get<std::string>(index.get(0));
    int target_int = std::stoi(max_value) + 1;
    Indexes i;
    i.push(std::to_string(target_int));
    row.insert(row.begin(), std::to_string(target_int));
    // std::cout << "target_int"<< target_int << std::endl;
    master_index.insert(i, row);
    // master_index.print();
    return "insert one row successfully";
}

void Table::load_second_indexes() {
    std::vector<std::string> index_files = File::match_files("./" + _table_name, "index");
    for (auto it: index_files) {
        std::pair<std::vector<std::string>, DBBPlusTree<std::string>> res = read_index_file(
                "./" + _table_name + "/" + it);
        second_indexes[res.first] = res.second;
    }
}

// todo: 解决索引值根据列类型动态变化, 主键值不一定为string
std::pair<std::vector<std::string>, DBBPlusTree<std::string>> Table::read_index_file(std::string filename) {
    auto fs = File::read(filename);
    // read column names of index
    std::string line;
    std::getline(fs, line);
    std::istringstream iss(line);
    std::vector<std::string> cols((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    DBBPlusTree<std::string> index_tree;

    while (!fs.eof()) {
        std::string val;
        Indexes index;
        for (int i = 0; i < cols.size(); i++) {
            fs >> val;
            index.push(val);
        }
        fs >> val;
        index_tree.insert(index, val);
    }
    return {cols, index_tree};
}


void Table::load_cols_type() {
    std::string frm_file = "./" + _table_name + "/" + _table_name + ".frm";
    auto is = File::read(frm_file);
    while (!is.eof()) {
        std::string col_name;
        int col_type;
        is >> col_name >> col_type;
        // std::cout << col_name << " " << col_type << std::endl;
        cols_type.push_back({col_name, col_type});
    }
    is.close();
}

std::vector<std::pair<std::string, int>> Table::get_cols_type() {
    return cols_type;
}

void Table::save() {
    master_index.save_to_file(get_data_file());
}

void Table::load_data_from_file() {
    // todo: hanle empty file
    if(!File::file_exists(get_data_file())){
        File::create_empty_file(get_data_file());
    }

    auto is = File::read(get_data_file());
    if (!is.good())
        std::cout << "Error: " << strerror(errno) << std::endl;
    // std::cout << "load data: " << std::endl;
    while (!File::file_is_empty_or_eof(is)) {
        // std::cout << "get from file" << std::endl;
        std::string primary_key;
        is >> primary_key;
        // 最后还有个换行符, 判断,跳过
        if(primary_key == "")
            continue;
        Indexes i(primary_key);

        std::string val;
        std::vector<std::string> row;
        for (int i = 0; i < cols_type.size(); i++) {
            is >> val;
            row.push_back(val);
        }
        master_index.insert(i, row);
    }
    is.eof();
}

std::string Table::get_data_file() {
    return "./" + _table_name + "/" + _table_name + ".idb";
}

std::vector<std::pair<DBBPlusTree<std::vector<std::string>>::DataNode *, int>> Table::select(GramTree *cond) {
    // todo: use index tree to select
   std::vector<std::pair<DBBPlusTree<std::vector<std::string>>::DataNode *, int>> v;
    auto all_leaf = master_index.preorder_traversal(master_index.rootBlock);
    for (int i = 0; i < all_leaf.size(); i++) {
        for(int j = 0; j < all_leaf[i]->node_num; j++){
            // todo: check if row match cond or not
            // mock: true
            v.push_back({all_leaf[i],j});
        }
    }
    return v;
}


