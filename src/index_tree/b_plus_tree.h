#ifndef DBMS_B_PLUS_TREE_H
#define DBMS_B_PLUS_TREE_H

#include "index.h"
#include <list>

template<typename IndexType, typename DataType>
struct Node{
    Node<IndexType, DataType> *parent;
    Node<IndexType, DataType> *next_leaf;
    Node<IndexType, DataType> *pre_leaf;
    std::vector<IndexType> indexes;
    std::vector<Node *> children;
    std::vector<DataType> data;


    Node(){
        parent = nullptr;
        next_leaf = nullptr;
        pre_leaf = nullptr;
    }

    int size(){
        return indexes.size();
    }

    bool is_leaf(){
        return children.size() == 0;
    }

    bool is_root(){
        return parent == nullptr;
    }
};

template<typename IndexType, typename DataType>
class BPlusTree{
private:
    int _max_leaf_num;
    using DataNode = Node<IndexType, DataType>;
    DataNode *_root;
    DataNode *_leftmost_leaf;
    DataNode *_rightmost_leaf;
    bool _data_found;

public:
    BPlusTree(int max_leaf_num = 5);

    void insert(IndexType index, DataType data);

    void insert_node(DataNode *node, IndexType index, DataType data);

    void split_non_leaf(DataNode *node);

    void split_leaf(DataNode *node);

    void print();

    void _print(std::vector<DataNode *> nodes);

    void del(IndexType index);

    void delete_index(DataNode *cur_node, IndexType index, int cur_node_pos);

    void redistribute_node(DataNode *left_node, DataNode *right_node, int pos_of_left_node,
                           int which_one_is_cur_node);

    void merge_node(DataNode *left_node, DataNode *right_node, int pos_of_right_node);

    std::list<IndexType> get_forward_index_list();

    std::list<IndexType> get_reverse_index_list();
};

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::insert_node(BPlusTree::DataNode *node, IndexType index, DataType data){
    // std::cout << "insert_node: " << std::endl;
    for(int i = 0; i <= node->size(); i++){
        // 如果已经遍历完该节点的所有index
        if(i == node->size()){
            if(node->is_leaf()){
                node->indexes.push_back(index);
                node->data.push_back(data);
                break;
            }else{
                insert_node(node->children[i], index, data);
                if(node->size() == _max_leaf_num)
                    split_non_leaf(node);
                return;
            }
        }

        if(index < node->indexes[i] && !node->is_leaf()){
            insert_node(node->children[i], index, data);
            if(node->size() == _max_leaf_num)
                split_non_leaf(node);
            return;
        }else if(index < node->indexes[i] && node->is_leaf()){
            std::swap(node->indexes[i], index);
            std::swap(node->data[i], data);
        }
    }

    if(node->size() == _max_leaf_num)
        split_leaf(node);
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::split_non_leaf(BPlusTree::DataNode *node){
    int mid, i;

    // 因为是非叶子节点, 所以需要提取中间孩子节点到父亲节点, 并且抛弃中间孩子节点
    // 如果最大叶子节点是奇数, 左孩子节点数=右孩子节点数=n/2
    // 如果最大叶子节点是偶数, 左孩子节点数=右孩子节点数+1=n/2
    mid = _max_leaf_num / 2;

    // 将当前节点(node)作为左孩子, right_node作为右孩子
    DataNode *right_node = new DataNode();
    auto mid_index = node->indexes[mid];
    std::move(node->indexes.begin() + mid + 1, node->indexes.end(), std::back_inserter(right_node->indexes));
    node->indexes.erase(node->indexes.begin() + mid, node->indexes.end());

    std::move(node->children.begin() + mid + 1, node->children.end(), std::back_inserter(right_node->children));
    node->children.erase(node->children.begin() + mid + 1, node->children.end());


    for(int i = 0; i < right_node->children.size(); i++){
        right_node->children[i]->parent = right_node;
    }


    if(node->is_root()){
        // 如果当前节点是根节点, 则new新节点作为父节点
        DataNode *parent = new DataNode();
        parent->indexes.push_back(mid_index);
        parent->children.push_back(node);
        parent->children.push_back(right_node);
        node->parent = parent;
        right_node->parent = parent;
        _root = parent;
        return;
    }else{
        // 如果当前节点不是根节点
        // 此处将node->parent赋值给node
        node = node->parent;
        DataNode *new_child_node = right_node;

        // 插入待分裂的非叶子节点的中间索引到其父亲节点中
        for(i = 0; i <= node->size(); i++){
            if(i == node->size()){
                node->indexes.push_back(mid_index);
                break;
            }
            if(mid_index < node->indexes[i]){
                std::swap(node->indexes[i], mid_index);
            }
        }


        // 将右节点插入到父亲节点的孩子指针中
        new_child_node->parent = node;
        for(int i = 0; i <= node->children.size(); i++){
            if(i == node->children.size()){
                node->children.push_back(new_child_node);
                break;
            }else if(new_child_node->indexes[0] < node->children[i]->indexes[0]){
                // 通过判断孩子节点的最左边索引来判断插入到哪个节点
                std::swap(node->children[i], new_child_node);
            }
        }
    }

}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::split_leaf(BPlusTree::DataNode *node){
    int mid, i;
    // 因为是叶子节点, 所以需要提取中间孩子节点到父亲节点,并保留所有叶子节点
    // 如果最大叶子节点是奇数, 左孩子节点数-1=右孩子节点数=n/2
    // 如果最大叶子节点是偶数, 左孩子节点数=右孩子节点数=n/2
    if(_max_leaf_num % 2)
        mid = (_max_leaf_num + 1) / 2;
    else mid = _max_leaf_num / 2;

    // 将当前节点(node)作为左孩子, right_node作为右孩子
    DataNode *right_node = new DataNode();
    auto mid_index = node->indexes[mid];
    std::move(node->indexes.begin() + mid, node->indexes.end(), std::back_inserter(right_node->indexes));
    node->indexes.erase(node->indexes.begin() + mid, node->indexes.end());

    std::move(node->data.begin() + mid, node->data.end(), std::back_inserter(right_node->data));
    node->data.erase(node->data.begin() + mid, node->data.end());

    node->children.clear();
    right_node->children.clear();

    // 更新指针
    right_node->next_leaf = node->next_leaf;
    right_node->pre_leaf = node;
    if(node->next_leaf)
        node->next_leaf->pre_leaf = right_node;
    node->next_leaf = right_node;

    if(node->is_root()){
        // 如果叶子节点是根节点, 则new新节点作为根节点
        DataNode *parent = new DataNode();
        parent->indexes.push_back(mid_index);
        parent->children.push_back(node);
        parent->children.push_back(right_node);
        node->parent = parent;
        right_node->parent = parent;
        _root = parent;
        _leftmost_leaf = node;
        _rightmost_leaf = right_node;
        return;
    }else{
        // 如果叶子节点不是根节点
        node = node->parent;
        DataNode *new_child_node = right_node;

        // 插入待分裂的叶子节点的中间索引及数据到其父亲节点中
        for(i = 0; i <= node->size(); i++){
            if(i == node->size()){
                node->indexes.push_back(mid_index);
                break;
            }
            if(mid_index < node->indexes[i]){
                std::swap(node->indexes[i], mid_index);
            }
        }


        new_child_node->parent = node;
        // 将右孩子节点插入到父节点的孩子节点中去, 左孩子已经在孩子节点中,无须操作
        // ps: 这里的node已经指向插入节点的父亲了
        for(int i = 0; i <= node->children.size(); i++){
            if(i == node->children.size()){
                node->children.push_back(new_child_node);
                break;
            }
            if(new_child_node->indexes[0] < node->children[i]->indexes[0]){
                std::swap(node->children[i], new_child_node);
            }
        }

        if(!right_node->next_leaf)
            _rightmost_leaf = right_node;
    }
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::insert(IndexType index, DataType data){
    insert_node(_root, index, data);
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::print(){
    std::vector<DataNode *> nodes;
    nodes.push_back(_root);
    _print(nodes);
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::_print(std::vector<DataNode *> nodes){
    // std::cout << "----------" << std::endl;
    std::vector<DataNode *> newBlocks;
    for(int i = 0; i < nodes.size(); i++){
        DataNode *cur_node = nodes[i];
        if(cur_node->data.size() == 0 && cur_node->indexes.size() != cur_node->children.size() - 1)
            std::cout << "index node error" << std::endl;
        if(cur_node->data.size() != 0 &&
           (cur_node->children.size() != 0 || cur_node->data.size() != cur_node->indexes.size()))
            std::cout << "leaf node error" << std::endl;
        std::cout << "[|";
        int j;
        if(cur_node->size() == 0)
            std::cout << "[空] ";
        for(j = 0; j < cur_node->size(); j++){
            // if(cur_node->is_leaf())
            //     std::cout << cur_node->indexes[j] << "(" << cur_node->data[j] << ")" << "|";
            // else
            std::cout << cur_node->indexes[j] << "|";
            std::cout.flush();
        }
        for(int k = 0; k < cur_node->children.size(); ++k){
            newBlocks.push_back(cur_node->children[k]);
        }
        std::cout << "]  ";
    }

    if(newBlocks.size() == 0){
        puts("");
        puts("");
        nodes.clear();
    }else{
        puts("");
        puts("");
        nodes.clear();
        _print(newBlocks);
    }
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::del(IndexType index){
    _data_found = false;
    delete_index(_root, index, 0);
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::delete_index(BPlusTree::DataNode *cur_node, IndexType index, int cur_node_pos){
    IndexType pre_leftmost_index = cur_node->indexes[0];

    for(int i = 0; _data_found == false && i <= cur_node->size(); i++){
        // 如果已经遍历过所有索引, 则判断是否大于最后一个索引,且最后一个孩子节点是否为空
        if(i == cur_node->size()){
            // todo: is_leaf貌似没必要
            if(index >= cur_node->indexes[i - 1] && !cur_node->is_leaf()){
                delete_index(cur_node->children[i], index, i);
            }
            break;
        }

        if(index < cur_node->indexes[i] && !cur_node->is_leaf()){
            delete_index(cur_node->children[i], index, i);
        }else{
            if(index == cur_node->indexes[i] && cur_node->is_leaf()){
                cur_node->indexes.erase(cur_node->indexes.begin() + i);
                cur_node->data.erase(cur_node->data.begin() + i);
                _data_found = true;
                // todo: rm parent is_root?
                // if(cur_node->size() == 0 && !cur_node->is_root() && !cur_node->parent->is_root())
                //     cur_node->parent->children[cur_node_pos] = nullptr;
                break;
            }
            // todo: 考虑如果不存在这个元素则抛出异常,这样可以减少删除之前的查找是否存在?
        }
    }

    if(cur_node->is_root() && cur_node->is_leaf()){
        return;
    }

    if(cur_node->is_root() && !cur_node->is_leaf() && cur_node->size() == 0){
        _root = cur_node->children[0];
        _root->parent = nullptr;
        return;
    }


    if(cur_node->is_leaf() && !cur_node->is_root()){
        if(cur_node_pos == 0){
            DataNode *right_node = cur_node->parent->children[1];
            if(right_node != nullptr && right_node->size() > (_max_leaf_num + 1) / 2){
                // 如果右兄弟节点存在且其index数量大于最大节点数的一半,则向其借一个元素
                redistribute_node(cur_node, right_node, 0, 0);
            }else if(right_node != nullptr && cur_node->size() + right_node->size() < _max_leaf_num){
                // 如果左右节点的index数数量加起来小于最大节点数
                merge_node(cur_node, right_node, 1);
            }
        }else{
            // 优先考虑左孩子,不符合条件再考虑右孩子节点(如果存在的话)
            DataNode *left_node = cur_node->parent->children[cur_node_pos - 1];
            DataNode *right_node = nullptr;
            if(cur_node_pos + 1 < cur_node->parent->children.size())
                right_node = cur_node->parent->children[cur_node_pos + 1];


            if(left_node != nullptr && left_node->size() > (_max_leaf_num + 1) / 2){
                redistribute_node(left_node, cur_node, cur_node_pos - 1, 1);
            }else if(right_node != nullptr && right_node->size() > (_max_leaf_num + 1) / 2){
                redistribute_node(cur_node, right_node, cur_node_pos, 0);
            }else if(left_node != nullptr && cur_node->size() + left_node->size() < _max_leaf_num){
                merge_node(left_node, cur_node, cur_node_pos);
            }else if(right_node != nullptr && cur_node->size() + right_node->size() < _max_leaf_num){
                merge_node(cur_node, right_node, cur_node_pos + 1);
            }
        }
    }else if(!cur_node->is_leaf() && !cur_node->is_root()){

        if(cur_node_pos == 0){
            DataNode *right_node = cur_node->parent->children[1];
            if(right_node != nullptr && right_node->size() - 1 >= ceil((_max_leaf_num - 1) / 2)){
                redistribute_node(cur_node, right_node, 0, 0);
            }else if(right_node != nullptr && cur_node->size() + right_node->size() < _max_leaf_num - 1){
                merge_node(cur_node, right_node, 1);
            }
        }else{
            DataNode *left_node = cur_node->parent->children[cur_node_pos - 1];

            DataNode *right_node = nullptr;
            if(cur_node_pos + 1 < cur_node->parent->children.size())
                right_node = cur_node->parent->children[cur_node_pos + 1];

            if(left_node != nullptr && left_node->size() - 1 >= ceil((_max_leaf_num - 1) / 2)){
                redistribute_node(left_node, cur_node, cur_node_pos - 1, 1);
            }else if(right_node != nullptr && right_node->size() - 1 >= ceil((_max_leaf_num - 1) / 2)){
                redistribute_node(cur_node, right_node, cur_node_pos, 0);
            }else if(left_node != nullptr && cur_node->size() + left_node->size() < _max_leaf_num - 1){
                merge_node(left_node, cur_node, cur_node_pos);
            }else if(right_node != nullptr && cur_node->size() + right_node->size() < _max_leaf_num - 1){
                merge_node(cur_node, right_node, cur_node_pos + 1);
            }
        }

    }

    // 如果父辈节点出现了待删除索引,则删除
    DataNode *tmp_node = cur_node->parent;
    while(tmp_node != nullptr){
        for(int i = 0; i < tmp_node->size(); i++){
            if(tmp_node->indexes[i] == pre_leftmost_index){
                tmp_node->indexes[i] = cur_node->indexes[0];
                break;
            }
        }
        tmp_node = tmp_node->parent;
    }
}

template<typename IndexType, typename DataType>
void
BPlusTree<IndexType, DataType>::redistribute_node(BPlusTree::DataNode *left_node, BPlusTree::DataNode *right_node,
                                                  int pos_of_left_node, int which_one_is_cur_node){

    IndexType pre_right_first_index = right_node->indexes[0];
    if(which_one_is_cur_node == 0){
        // 左节点是当前节点, 即需要从右节点移动第一个元素到左节点

        if(!left_node->is_leaf()){
            // 重组织非索引节点
            left_node->indexes.push_back(left_node->parent->indexes[pos_of_left_node]);
            left_node->children.push_back(right_node->children[0]);
            for(int i = 0; i < left_node->children.size(); i++){
                left_node->children[i]->parent = left_node;
            }

            left_node->parent->indexes[pos_of_left_node] = right_node->indexes[0];

            right_node->indexes.erase(right_node->indexes.begin());
            right_node->children.erase(right_node->children.begin());
        }else{
            // 重组织叶子节点
            left_node->indexes.push_back(right_node->indexes[0]);
            left_node->data.push_back(right_node->data[0]);

            right_node->indexes.erase(right_node->indexes.begin());
            right_node->data.erase(right_node->data.begin());

            left_node->parent->indexes[pos_of_left_node] = right_node->indexes[0];
        }


    }else{
        // 右左节点是当前节点, 即需要从左节点移动最后一个元素到左节点
        if(!right_node->is_leaf()){
            right_node->indexes.insert(right_node->indexes.begin(), right_node->parent->indexes[pos_of_left_node]);
            right_node->children.insert(right_node->children.begin(), left_node->children.back());

            right_node->parent->indexes[pos_of_left_node] = left_node->indexes.back();

            for(int i = 0; i < right_node->children.size(); ++i){
                right_node->children[i]->parent = right_node;
            }

            left_node->indexes.pop_back();
            left_node->children.pop_back();
        }else{
            right_node->indexes.insert(right_node->indexes.begin(), left_node->indexes.back());
            right_node->data.insert(right_node->data.begin(), left_node->data.back());

            right_node->parent->indexes[pos_of_left_node] = right_node->indexes.front();

            left_node->indexes.pop_back();
            left_node->data.pop_back();
        }
    }
}

template<typename IndexType, typename DataType>
void BPlusTree<IndexType, DataType>::merge_node(BPlusTree::DataNode *left_node, BPlusTree::DataNode *right_node,
                                                int pos_of_right_node){
    if(!left_node->is_leaf()){
        left_node->indexes.push_back(left_node->parent->indexes[pos_of_right_node - 1]);
    }
    // todo: handle leaf node children nums
    left_node->indexes.insert(left_node->indexes.end(), right_node->indexes.begin(), right_node->indexes.end());
    left_node->data.insert(left_node->data.end(), right_node->data.begin(), right_node->data.end());
    left_node->children.insert(left_node->children.end(), right_node->children.begin(), right_node->children.end());

    for(int i = 0; i < left_node->children.size(); i++){
        if(left_node->children[i])
            left_node->children[i]->parent = left_node;
    }
    if(left_node->is_leaf()){
        left_node->next_leaf = right_node->next_leaf;
        if(right_node->next_leaf)
            right_node->next_leaf->pre_leaf = left_node;
        else
            _rightmost_leaf = left_node;
    }
    left_node->parent->indexes.erase(left_node->parent->indexes.begin() + pos_of_right_node - 1);
    left_node->parent->children.erase(left_node->parent->children.begin() + pos_of_right_node);
}

template<typename IndexType, typename DataType>
BPlusTree<IndexType, DataType>::BPlusTree(int max_leaf_num){
    // 该B+树只能支持大于等于3的最大叶子节点
    if(max_leaf_num <= 2)
        throw "max leaf num must >= 3: " + std::to_string(max_leaf_num);
    _max_leaf_num = max_leaf_num;
    _data_found = false;
    _root = new DataNode;
    _leftmost_leaf = _root;
    _rightmost_leaf = _root;
}

template<typename IndexType, typename DataType>
std::list<IndexType> BPlusTree<IndexType, DataType>::get_forward_index_list(){
    std::list<IndexType> l;
    for(auto tmp = _leftmost_leaf; tmp != nullptr; tmp = tmp->next_leaf){
        for(int i = 0; i < tmp->indexes.size(); i++){
            l.push_back(tmp->indexes[i]);
        }
    }
    return l;
}

template<typename IndexType, typename DataType>
std::list<IndexType> BPlusTree<IndexType, DataType>::get_reverse_index_list(){
    std::list<IndexType> l;
    for(auto tmp = _rightmost_leaf; tmp != nullptr; tmp = tmp->pre_leaf){
        for(int i = tmp->indexes.size() - 1; i >= 0; i--){
            l.push_back(tmp->indexes[i]);
        }
    }
    return l;
}

#endif //DBMS_B_PLUS_TREE_H
