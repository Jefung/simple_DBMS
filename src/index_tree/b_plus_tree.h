#ifndef DBMS_B_PLUS_TREE_H
#define DBMS_B_PLUS_TREE_H

// #include <index_tree.h>
// #include <index_tree.h>
// #include <index_tree.h>
#include "index.h"
// #include "../index_tree.h"

template<typename DataType>
struct Node{
    int node_num;
    Node<DataType> *parent;
    Node<DataType> *next_leaf;
    Node<DataType> *pre_leaf;
    std::vector<Index> indexes;
    std::vector<Node *> children;
    std::vector<DataType> data;
    bool is_leaf;


    Node(){
        node_num = 0;
        parent = NULL;
        next_leaf = NULL;
        pre_leaf = NULL;
        is_leaf = false;
        children.push_back(nullptr);
    }

    int size(){
        return indexes.size();
    }
};

template<typename DataType>
class BPlusTree{
private:
    int _max_leaf_num;
    using DataNode = Node<DataType>;
    DataNode *_root = new DataNode;
    bool _data_found;

public:
    BPlusTree(int max_leaf_num = 5) : _max_leaf_num(max_leaf_num), _data_found(false){};

    void insert(Index index, DataType data);

    void insert_node(DataNode *node, Index index, DataType data);

    void split_non_leaf(DataNode *node);

    void split_leaf(DataNode *node);

    void print();

    void _print(std::vector<DataNode *> nodes);
};

template<typename DataType>
void BPlusTree<DataType>::insert_node(BPlusTree::DataNode *node, Index index, DataType data){
    for(int i = 0; i <= node->size(); i++){
        if(i == node->size()){
            if(node->children[i] != nullptr){
                insert_node(node->children[i], index, data);
                if(node->size() == _max_leaf_num)
                    split_non_leaf(node);
                return;
            }else{
                node->indexes.push_back(index);
                node->children.push_back(nullptr);
                node->data.push_back(data);
                break;
            }
        }

        if(index < node->indexes[i] && node->children[i] != nullptr){
            insert_node(node->children[i], index, data);
            if(node->size() == _max_leaf_num)
                split_non_leaf(node);
            return;
        }else if(index < node->indexes[i] && node->children[i] == NULL){
            std::swap(node->indexes[i], index);
            std::swap(node->data[i], data);
        }
    }

    if(node->size() == _max_leaf_num)
        split_leaf(node);
}

template<typename DataType>
void BPlusTree<DataType>::split_non_leaf(BPlusTree::DataNode *node){
    std::cout << "slipt_non_leaf: " << std::endl;
    int mid, i, j;

    // 因为是非叶子节点, 所以需要提取中间孩子节点到父亲节点, 并且抛弃中间孩子节点
    // 如果最大叶子节点是奇数, 左孩子节点数=右孩子节点数=n/2
    // 如果最大叶子节点是偶数, 左孩子节点数=右孩子节点数+1=n/2
    mid = _max_leaf_num / 2;

    // 将当前节点(node)作为左孩子, right_node作为右孩子
    DataNode *right_node = new DataNode();
    auto mid_index = node->indexes[mid];
    std::move(node->indexes.begin() + mid + 1, node->indexes.end(), std::back_inserter(right_node->indexes));
    node->indexes.erase(node->indexes.begin() + mid, node->indexes.end());

    auto mid_data = node->data[mid];
    std::move(node->data.begin() + mid + 1, node->data.end(), std::back_inserter(right_node->data));
    node->data.erase(node->data.begin() + mid, node->data.end());

    right_node->children.clear();
    std::move(node->children.begin() + mid + 1, node->children.end(), std::back_inserter(right_node->children));
    node->children.erase(node->children.begin() + mid + 1, node->children.end());


    for(int i = 0; i < node->children.size(); i++){
        node->children[i]->parent = node;
    }
    for(int i = 0; i < right_node->children.size(); i++){
        right_node->children[i]->parent = right_node;
    }


    if(node->parent == NULL){
        // 如果当前节点是根节点, 则new新节点作为父节点
        DataNode *parent = new DataNode();
        parent->parent = NULL;
        parent->indexes.push_back(mid_index);
        parent->data.push_back(mid_data);
        parent->children[0] = node;
        parent->children.push_back(right_node);
        node->parent = parent;
        right_node->parent = parent;
        _root = parent;
        return;
    }else{
        // 如果当前节点不是根节点

        // we have to put the val and assign the rightBlock to the right place in the parentBlock
        // so we go to the parentBlock and from now we consider the curBlock as the parentBlock of the splitted Node
        // 此处将node->parent赋值给node
        node = node->parent;
        DataNode *new_child_node = right_node;

        // 插入待分裂的非叶子节点的中间索引及数据到其父亲节点中
        for(i = 0; i <= node->size(); i++){
            if(i == node->size()){
                node->indexes.push_back(mid_index);
                node->data.push_back(mid_data);
                // 这里额外插入一个nullptr供下面插入孩子节点使用
                // 保证了孩子节点数 = 索引节点数+1 = 数据节点数+1
                node->children.push_back(nullptr);
            }
            if(mid_index < node->indexes[i]){
                std::swap(node->indexes[i], mid_index);
                std::swap(node->data[i], mid_data);
            }
        }


        // 将右节点插入到父亲节点的孩子指针中
        for(int i = 0; i < node->children.size(); i++){
            if(node->children[i] == nullptr){
                node->children[i] = new_child_node;
                break;
            }else if(new_child_node->indexes[0] < node->children[i]->indexes[0]){
                // 通过判断孩子节点的最左边索引来判断插入到哪个节点
                std::swap(node->children[i], new_child_node);
            }
        }

        // 更新所有孩子节点的父亲指针指向node
        // todo: 考虑直接把right_node的父亲指针指向node?
        for(int i = 0; i < node->children.size(); i++){
            node->children[i]->parent = node;
        }
    }

}

template<typename DataType>
void BPlusTree<DataType>::split_leaf(BPlusTree::DataNode *node){
    std::cout << "split_leaf" << std::endl;
    int mid, i, j;
    // 因为是叶子节点, 所以需要提取中间孩子节点到父亲节点,并保留所有叶子节点
    // 如果最大叶子节点是奇数, 左孩子节点数-1=右孩子节点数=n/2
    // 如果最大叶子节点是偶数, 左孩子节点数=右孩子节点数=n/2
    if(_max_leaf_num % 2)
        mid = (_max_leaf_num + 1) / 2;
    else mid = _max_leaf_num / 2;

    // 将当前节点(node)作为左孩子, right_node作为右孩子
    DataNode *right_node = new DataNode();
    auto mid_index = node->indexes[mid];
    auto mid_data = node->data[mid];
    std::move(node->indexes.begin() + mid, node->indexes.end(), std::back_inserter(right_node->indexes));
    node->indexes.erase(node->indexes.begin() + mid, node->indexes.end());

    std::move(node->data.begin() + mid, node->data.end(), std::back_inserter(right_node->data));
    node->data.erase(node->data.begin() + mid, node->data.end());

    // todo: 考虑将叶子节点的孩子指针清空, 而不是用nullptr来保证索引节点数+1=孩子节点数
    node->children.clear();
    for(int i = 0; i <= node->indexes.size(); i++){
        node->children.push_back(nullptr);
    }
    right_node->children.clear();
    for(int i = 0; i <= right_node->indexes.size(); i++){
        right_node->children.push_back(nullptr);
    }

    if(node->parent == NULL){
        // 如果叶子节点是根节点, 则new新节点作为根节点
        // std::cout << "split leaf: " << node->size() << " " << right_node->size() << std::endl;
        DataNode *parent = new DataNode();
        parent->parent = NULL;
        parent->indexes.push_back(mid_index);
        parent->data.push_back(mid_data);
        parent->children[0] = node;
        parent->children.push_back(right_node);
        node->parent = parent;
        right_node->parent = parent;
        _root = parent;
        return;
    }else{
        // 如果叶子节点不是根节点

        node = node->parent;

        DataNode *new_child_node = right_node;

        // 插入待分裂的叶子节点的中间索引及数据到其父亲节点中
        for(i = 0; i <= node->size(); i++){
            if(i == node->size()){
                node->indexes.push_back(mid_index);
                node->data.push_back(mid_data);
                break;
            }
            if(mid_index < node->indexes[i]){
                std::swap(node->indexes[i], mid_index);
                std::swap(node->data[i], mid_data);
            }
        }



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

        // 更新孩子节点的父亲指针指向
        for(int i = 0; i < node->children.size(); i++){
            node->children[i]->parent = node;
            std::cout << node->children[i]->indexes[0] << std::endl;
        }
    }
}

template<typename DataType>
void BPlusTree<DataType>::insert(Index index, DataType data){
    insert_node(_root, index, data);
}

template<typename DataType>
void BPlusTree<DataType>::print(){
    _print({_root});
}

template<typename DataType>
void BPlusTree<DataType>::_print(std::vector<DataNode *> nodes){

    std::vector<DataNode *> newBlocks;
    for(int i = 0; i < nodes.size(); i++){
        DataNode *cur_node = nodes[i];
        std::cout << "[|";
        int j;
        for(j = 0; j < cur_node->size(); j++){
            std::cout << cur_node->indexes[j] << "|";
            if(cur_node->children[j] != nullptr){
                newBlocks.push_back(cur_node->children[j]);
            }
        }

        if(cur_node->children[j] != nullptr){
            newBlocks.push_back(cur_node->children[j]);
        }

        std::cout << "]  ";
    }

    if(newBlocks.size() == 0){
        //if there is no childBlock block left to send out then just the end of the recursion
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


#endif //DBMS_B_PLUS_TREE_H
