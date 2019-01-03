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
        is >> col_name;
        if (col_name == "")
            continue;
        is >> col_type;
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
    if (!File::file_exists(get_data_file())) {
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
        if (primary_key == "")
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

std::vector<std::pair<DBBPlusTree<std::vector<std::string>>::DataNode *, int>> Table::get_suitable_rows(GramTree *cond) {
    // todo: use index tree to get_suitable_rows
    std::vector<std::pair<DBBPlusTree<std::vector<std::string>>::DataNode *, int>> rows;
    auto all_leaf = master_index.preorder_traversal(master_index.rootBlock);
    for (int i = 0; i < all_leaf.size(); i++) {
        for (int j = 0; j < all_leaf[i]->node_num; j++) {
            // todo: check if row match cond or not
            // mock: true
            std::vector<std::string> row = all_leaf[i]->data[j];
            if (match_cond(cond, row))
                rows.push_back({all_leaf[i], j});
        }
    }
    return rows;
}

bool Table::match_cond(GramTree *cond, std::vector<std::string> row) {

    if (!cond)
        return true;
    if (cond->getType() == GramTree::GRAM_CONDITION)
        cond = cond->getChild(0);
    std::string cond_type(cond->getStrValue());
    // std::cout << "cond_type: " << cond_type << std::endl;
    if (cond_type == "or")
        return log_or(cond, row);

    if (cond_type == "and")
        return log_and(cond, row);

    if (cond_type == "<")
        return compare_less(cond, row);

    if (cond_type == ">")
        return compare_greater(cond, row);

    if (cond_type == ">=")
        return compare_greater_equal(cond, row);

    if (cond_type == "<=")
        return compare_less_equal(cond, row);

    if (cond_type == "=")
        return compare_equal(cond, row);

    if (cond->getType() == GramTree::GRAM_ISNULL)
        return is_null(cond->getChild(0), row);

    if (cond->getType() == GramTree::GRAM_NOTNULL)
        return not_null(cond->getChild(0), row);

    // if(cond->getType() == GramTree::GRAM_OPERATION)
    // return

    throw "cond error!!!";
}

bool Table::log_or(GramTree *cond, std::vector<std::string> row) {
    return match_cond(cond->getChild(0), row) || match_cond(cond->getChild(1), row);
}

bool Table::log_and(GramTree *cond, std::vector<std::string> row) {
    return match_cond(cond->getChild(0), row) && match_cond(cond->getChild(1), row);
}

// todo: < 只比较数字
bool Table::compare_less(GramTree *cond, std::vector<std::string> row) {
    int i1 = factor(cond->getChild(0), row);
    int i2 = factor(cond->getChild(1), row);
    return i1 < i2;
}

int Table::get_col_pos(std::string col_name) {
    for (int i = 0; i < cols_type.size(); i++) {
        if (cols_type[i].first == col_name)
            return i;
    }
    throw "col " + col_name + " doesn't exists";
}

// todo: > 只比较数字
bool Table::compare_greater(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) > factor(cond->getChild(1), row);
}

// todo: = 可以比较字符串, 数字
bool Table::compare_equal(GramTree *cond, std::vector<std::string> row) {
    // 比较字符串
    if (cond->getChild(0)->getType() == GramTree::GRAM_STRVALUE ||
        cond->getChild(1)->getType() == GramTree::GRAM_STRVALUE) {
        bool flag1 = false;
        bool flag2 = false;
        std::string s1;
        std::string s2;
        std::string col1;
        std::string col2;
        // todo: 假定这里只有字符串,数字或者列名
        if (cond->getChild(0)->getType() == GramTree::GRAM_STRVALUE) {
            flag1 = true;
            s1 = cond->getChild(0)->getStrValue();
        } else {
            col1 = cond->getChild(0)->getStrValue();
        }
        if (cond->getChild(1)->getType() == GramTree::GRAM_STRVALUE) {
            flag2 = true;
            s2 = cond->getChild(1)->getStrValue();
        } else {
            col1 = cond->getChild(1)->getStrValue();
        }

        if (!flag1)
            s1 = row[get_col_pos(col1)];
        if (!flag2)
            s2 = row[get_col_pos(col1)];
        // std::cout << s1 << "=" << s2 << std::endl;
        return s1.compare(s2) == 0;
    } else {
        return !compare_less(cond, row) && !compare_greater(cond, row);
    }
}

bool Table::compare_greater_equal(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) >= factor(cond->getChild(1), row);
}

bool Table::compare_less_equal(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) <= factor(cond->getChild(1), row);
}

bool Table::is_null(GramTree *cond, std::vector<std::string> row) {
    // todo: 暂定空字符串为空的
    std::string col_name = cond->getStrValue();
    int i = get_col_pos(col_name);
    // std::cout << "row[" << i << "]: " << row[i] << std::endl;
    std::string str = row[i];
    return str.compare("\"\"") == 0;
    // return row[i] == """";
}

bool Table::not_null(GramTree *cond, std::vector<std::string> row) {
    return !is_null(cond, row);
}

int Table::operation(GramTree *cond, std::vector<std::string> row) {
    std::string op = cond->getStrValue();
    if (op == "UMINUS")
        return umius(cond, row);
    if (op == "+")
        return plus(cond, row);
    if (op == "-")
        return minus(cond, row);
    if (op == "*")
        return muliply(cond, row);
    if (op == "/")
        return devide(cond, row);
    throw "operator error!";
}

int Table::umius(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row);
    // if (cond->getChild(0)->getType() == GramTree::GRAM_NUMVALUE)
    //     return -cond->getChild(0)->getNumValue();
    //
    // if (cond->getChild(0)->getType() == GramTree::GRAM_OPERATION)
    //     return -operation(cond->getChild(0), row);
    // if (cond->getChild(0)->getType() == GramTree::GRAM_COLUMN) {
    //     int pos = get_col_pos(cond->getChild(0)->getStrValue());
    //     if (cols_type[pos].second != 0)
    //         throw "operator object must int";
    //     return std::stoi(row[pos]);
    // }
    // throw "umius operator objuect must int";
}

int Table::plus(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) + factor(cond->getChild(1), row);
    // return 0;
}

int Table::factor(GramTree *cond, std::vector<std::string> row) {
    // std::cout << cond->getType() << std::endl;
    switch (cond->getType()) {
        case GramTree::GRAM_NUMVALUE:
            return cond->getNumValue();
        case GramTree::GRAM_OPERATION:
            return operation(cond, row);
        case GramTree::GRAM_COLUMN:
            int pos = get_col_pos(cond->getStrValue());
            if (cols_type[pos].second != 0)
                throw "operator object must int";
            // todo: 这里为空""""
            if (row[pos].compare("\"\"") == 0)
                return 0;
            else
                return std::stoi(row[pos]);
    }
    throw "factor object must int";
}

int Table::minus(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) - factor(cond->getChild(1), row);
    // return 0;
}

int Table::devide(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) / factor(cond->getChild(1), row);
}

int Table::muliply(GramTree *cond, std::vector<std::string> row) {
    return factor(cond->getChild(0), row) * factor(cond->getChild(1), row);
}

std::vector<std::vector<std::string>> Table::select(GramTree *tree) {
    // tree->showTree();
    auto rows = get_suitable_rows(tree->getChild(2));
    std::vector<std::vector<std::string>> res;
    for (auto it : rows) {
        std::vector<std::string> row = it.first->data[it.second];
        std::vector<std::string> tmp = selected_row_to_res(tree->getChild(1),row);
        res.push_back(tmp);
    }
    return res;
}

std::vector<std::string> Table::selected_row_to_res(GramTree* selected_list, std::vector<std::string> row) {
    std::vector<std::string> res;
    for (int i = 0; i < selected_list->getChildNum(); i++) {
        GramTree* node =selected_list->getChild(i);
        if(node->getType() == GramTree::GRAM_COLUMN){
            std::string type(node->getStrValue());
            if(type == "*")
                res.insert(res.end(),row.begin(),row.end());
            else{
                int pos = get_col_pos(type);
                res.push_back(row[pos]);
            }
            continue;
        }

        if(node->getType() == GramTree::GRAM_OPERATION){
            int i = operation(node,row);
            res.push_back(std::to_string(i));
            continue;
        }
        throw "columns list match be operation or column name";
    }
    return res;
}

int Table::update(GramTree *tree) {
    auto selected_nodes = get_suitable_rows(tree->getChild(2));
    // std::cout << "selected_nodes nums: " <<selected_nodes.size() << std::endl;
    int effected_row_count = 0;
    for (int i = 0; i < selected_nodes.size(); i++) {
        // auto row = selected_nodes[i].first->data[selected_nodes[i].second];
        for (int k = 0; k < tree->getChild(1)->getChildNum(); k++) {
            std::string col_name = tree->getChild(1)->getChild(k)->getStrValue();
            std::string new_val;

            if (tree->getChild(1)->getChild(k)->getChild(0)->getType() == GramTree::GRAM_NUMVALUE)
                new_val = std::to_string(tree->getChild(1)->getChild(k)->getChild(0)->getNumValue());
            else
                new_val = tree->getChild(1)->getChild(k)->getChild(0)->getStrValue();

            int col_pos = get_col_pos(col_name);

            selected_nodes[i].first->data[selected_nodes[i].second][col_pos] = new_val;
            effected_row_count++;
        }
        // master_index.print();
    }
    return effected_row_count;
}

int Table::del(GramTree *tree) {
    auto selected_nodes = get_suitable_rows(tree->getChild(1));
    int count = 0;
    for (int i = 0; i < selected_nodes.size(); i++) {
        Indexes index = selected_nodes[i].first->indexes[selected_nodes[i].second];
        master_index.del(index);
        count++;
    }
    return count;
}

// todo: 这里只有单索引, 用列名作为文件名: 列名.index
std::string Table::create_second_indexes(GramTree *tree) {
    std::string index_name = tree->getChild(0)->getStrValue();
    std::string col_name = tree->getChild(1)->getChild(0)->getStrValue();
    std::string index_file = "./" + _table_name + "/" + index_name + ".index";
    if(File::file_exists(index_file))
        return "index already exists";
    auto fs = File::overwrite(index_file);
    fs <<  col_name << std::endl;
    fs.close();
    return "create index sucessfully";
}

std::string Table::drop_second_indexes(GramTree *tree) {
    std::string index_name = tree->getChild(0)->getChild(0)->getStrValue();
    std::string index_file = "./" + _table_name + "/" + index_name + ".index";
    if(!File::file_exists(index_file))
        return "index not exists";
    else{
        if(File::rm_file(index_file))
            return "drop index sucessfully";
        else
            return "can't drop index : " + File::get_error();
    }
}




