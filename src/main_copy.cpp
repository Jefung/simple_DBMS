// #include<bits/stdc++.h>
// #include "boost/variant.hpp"
// #include <boost/any.hpp>
// #include <streambuf>
//
// class Indexes {
// private:
//     using IndexType = boost::variant<int, double, std::string>;
//     std::vector<IndexType> _v;
//     // int _size;
// public:
//     Indexes(int i) {
//         _v.push_back(i);
//     }
//
//     Indexes() {}
//
//     IndexType get(int index) const {
//         return _v[index];
//     }
//
//     int size() const {
//         return _v.size();
//     }
//
//     void push(const IndexType &i) {
//         _v.push_back(i);
//     }
//
//     friend std::ostream &operator<<(std::ostream &stream, const Indexes &i) {
//         for (int j = 0; j < i._v.size(); j++) {
//           stream << i._v[j]  << " ";
//         }
//         // stream << i._v[0];
//         return stream;
//     }
//
//     friend bool operator<(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) >= boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) >= boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) >= 0)
//                 return false;
//
//         }
//         return true;
//     }
//
//     friend bool operator==(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) != boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) != boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) != 0)
//                 return false;
//         }
//         return true;
//     }
//
//     friend bool operator>(const Indexes &i1, const Indexes &i2) {
//         int size = i1.size() > i2.size() ? i2.size() : i1.size();
//         for (int i = 0; i < size; i++) {
//             if (i1.get(i).which() != i2.get(i).which())
//                 throw "type of indexes is not same";
//
//             if (i1.get(i).which() == 0 && boost::get<int>(i1.get(i)) <= boost::get<int>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 1 && boost::get<double>(i1.get(i)) <= boost::get<double>(i2.get(i)))
//                 return false;
//             if (i1.get(i).which() == 2
//                 && boost::get<std::string>(i1.get(i)).compare(boost::get<std::string>(i2.get(i))) < 0)
//                 return false;
//         }
//         return true;
//     }
// };
//
// Indexes empty_index;
// using namespace std;
// #define MAX 50
//
// template<typename DataType>
// struct Node {
//     //number of nodes
//     int node_num;
//     //for parent Node and index
//     Node<DataType> *parentBlock;
//     //values
//     Indexes indexes[MAX];
//     //child Blocks
//     Node *childBlock[MAX];
//     DataType data[MAX];
//
//     Node() { //constructor to initialize a block
//         node_num = 0;
//         parentBlock = NULL;
//         for (int i = 0; i < MAX; i++) {
//             indexes[i] = empty_index;
//             childBlock[i] = NULL;
//         }
//     }
// };
//
//
// template<typename DataType>
// class DBBPlusTree {
// private:
//     using DataNode = Node<DataType>;
//     int numberOfPointers;
//     DataNode *rootBlock = new DataNode();
//     bool dataFound;
// public:
//     DBBPlusTree(int max_node_num) : numberOfPointers(max_node_num) {}
//
//     DataNode *get_root() {
//         return rootBlock;
//     }
//
//     int get_max_index(){
//         // todo: be to test
//         return _get_max_index(rootBlock);
//     }
//
//     int _get_max_index(DataNode *node){
//         if(!node)
//             return 0;
//         else{
//             if(node->childBlock[node->node_num] != NULL)
//                 return _get_max_index(node->childBlock[node->node_num]);
//             else
//                 return node->data[node->node_num-1];
//         }
//     }
//
//     //function to split the leaf nodes
//     void splitLeaf(DataNode *curBlock) {
//         int x, i, j;
//
//         //split the greater half to the left when numberOfPointer is odd
//         //else split equal equal when numberOfPointer is even
//         if (numberOfPointers % 2)
//             x = (numberOfPointers + 1) / 2;
//         else x = numberOfPointers / 2;
//
//         //we don't declare another block for leftBlock, rather re-use curBlock as leftBlock and
//         //take away the right half values to the rightBlock
//         DataNode *rightBlock = new DataNode();
//
//         //so leftBlock has x number of nodes
//         curBlock->node_num = x;
//         //and rightBlock has numberOfPointers-x
//         rightBlock->node_num = numberOfPointers - x;
//         //so both of them have their common parent [even parent may be null, so both of them will have null parent]
//         rightBlock->parentBlock = curBlock->parentBlock;
//
//         for (i = x, j = 0; i < numberOfPointers; i++, j++) {
//             //take the right-half values from curBlocks and put in the rightBlock
//             rightBlock->indexes[j] = curBlock->indexes[i];
//             rightBlock->data[j] = curBlock->data[i];
//             //and erase right-half values from curBlock to make it real leftBlock
//             //so that it does not contain all values only contains left-half values
//             curBlock->indexes[i] = empty_index;
//         }
//         //for splitting the leaf blocks we copy the first item from the rightBlock to their parentBlock
//         //and val contains that indexes
//         Indexes val = rightBlock->indexes[0];
//         DataType data = rightBlock->data[0];
//
//         //if the leaf itself is a parent then
//         if (curBlock->parentBlock == NULL) {
//             //it has null parent, so create_table a new parent
//             DataNode *parentBlock = new DataNode();
//             //and new parent should have a null parent
//             parentBlock->parentBlock = NULL;
//             //new parent will have only one member
//             parentBlock->node_num = 1;
//             //and that member is val
//             parentBlock->indexes[0] = val;
//             parentBlock->data[0] = data;
//             //so the parent has two child, so assign them (don't forget curBlock is actually the leftBlock)
//             parentBlock->childBlock[0] = curBlock;
//             parentBlock->childBlock[1] = rightBlock;
//             //their parent of the left and right blocks is no longer null, so assign their parent
//             curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
//             //from now on this parentBlock is the rootBlock
//             rootBlock = parentBlock;
//             return;
//         } else {   //if the splitted leaf block is not rootBlock then
//
//             // we have to put the val and assign the rightBlock to the right place in the parentBlock
//             // so we go to the parentBlock and from now we consider the curBlock as the parentBlock of the splitted Node
//
//             curBlock = curBlock->parentBlock;
//
//             //for the sake of insertNodeion sort to put the rightBlock and val in the exact position
//             //of th parentBlock [here curBlock] take a new child block and assign rightBlock to it
//             DataNode *newChildBlock = new DataNode();
//             newChildBlock = rightBlock;
//
//             //simple insertion sort to put val at the exact position of values[] in the parentBlock [here curBlock]
//
//             for (i = 0; i <= curBlock->node_num; i++) {
//                 if (val < curBlock->indexes[i]) {
//                     swap(curBlock->indexes[i], val);
//                     swap(curBlock->data[i], data);
//                 }
//             }
//
//             //after putting val number of nodes gets increase by one
//             curBlock->node_num++;
//
//             //simple insertNodeion sort to put rightBlock at the exact position
//             //of childBlock[] in the parentBlock [here curBlock]
//
//             for (i = 0; i < curBlock->node_num; i++) {
//                 if (newChildBlock->indexes[0] < curBlock->childBlock[i]->indexes[0]) {
//                     swap(curBlock->childBlock[i], newChildBlock);
//                 }
//             }
//             curBlock->childBlock[i] = newChildBlock;
//
//             //we reordered some blocks and pointers, so for the sake of safety
//             //all childBlocks' should have their parent updated
//             for (i = 0; curBlock->childBlock[i] != NULL; i++) {
//                 curBlock->childBlock[i]->parentBlock = curBlock;
//             }
//         }
//
//     }
//
//     //function to split the non leaf nodes
//     void splitNonLeaf(DataNode *curBlock) {
//         int x, i, j;
//
//         //split the less half to the left when numberOfPointer is odd
//         //else split equal equal when numberOfPointer is even.  n/2 does it nicely for us
//
//         x = numberOfPointers / 2;
//
//         //declare rightBlock and we will use curBlock as the leftBlock
//         DataNode *rightBlock = new DataNode();
//
//         //so leftBlock has x number of nodes
//         curBlock->node_num = x;
//         //rightBlock has numberOfPointers-x-1 children, because we won't copy and paste
//         //rather delete and paste the first item of the rightBlock
//         rightBlock->node_num = numberOfPointers - x - 1;
//         //both children have their common parent
//         rightBlock->parentBlock = curBlock->parentBlock;
//
//
//         for (i = x, j = 0; i <= numberOfPointers; i++, j++) {
//             //copy the right-half members to the rightBlock
//             rightBlock->indexes[j] = curBlock->indexes[i];
//             rightBlock->data[j] = curBlock->data[i];
//             //and also copy their children
//             rightBlock->childBlock[j] = curBlock->childBlock[i];
//             //erase the right-half values from curBlock to make it perfect leftBlock
//             //which won't contain only left-half values and their children
//             curBlock->indexes[i] = empty_index;
//             //erase all the right-half childBlocks from curBlock except the x one
//             //because if left child has 3 nodes then it should have 4 childBlocks, so don't delete that child
//             if (i != x)curBlock->childBlock[i] = NULL;
//         }
//
//         //we will take a copy of the first item of the rightBlock
//         //as we will delete that item later from the list
//         Indexes val = rightBlock->indexes[0];
//         DataType data = rightBlock->data[0];
//         //just right-shift indexes[] and childBlock[] by one from rightBlock
//         //to have no repeat of the first item for non-leaf Node
//         memcpy(&rightBlock->indexes, &rightBlock->indexes[1], sizeof(Indexes) * (rightBlock->node_num + 1));
//         memcpy(&rightBlock->data, &rightBlock->data[1], sizeof(DataType) * (rightBlock->node_num + 1));
//         memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock) * (rightBlock->node_num + 1));
//
//         //we reordered some values and positions so don't forget
//         //to assign the children's exact parent
//
//         for (i = 0; curBlock->childBlock[i] != NULL; i++) {
//             curBlock->childBlock[i]->parentBlock = curBlock;
//         }
//         for (i = 0; rightBlock->childBlock[i] != NULL; i++) {
//             rightBlock->childBlock[i]->parentBlock = rightBlock;
//         }
//
//         //if the splitted block itself a parent
//         if (curBlock->parentBlock == NULL) {
//             //create_table a new parent
//             DataNode *parentBlock = new DataNode();
//             //parent should have a null parent
//             parentBlock->parentBlock = NULL;
//             //parent will have only one node
//             parentBlock->node_num = 1;
//             //the only indexes is the val
//             parentBlock->indexes[0] = val;
//             parentBlock->data[0] = data;
//             //it has two children, leftBlock and rightBlock
//             parentBlock->childBlock[0] = curBlock;
//             parentBlock->childBlock[1] = rightBlock;
//
//             //and both rightBlock and leftBlock has no longer null parent, they have their new parent
//             curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
//
//             //from now on this new parent is the root parent
//             rootBlock = parentBlock;
//             return;
//         } else {   //if the splitted leaf block is not rootBlock then
//
//             // we have to put the val and assign the rightBlock to the right place in the parentBlock
//             // so we go to the parentBlock and from now we consider the curBlock as the parentBlock of the splitted Node
//             curBlock = curBlock->parentBlock;
//
//             //for the sake of insertNodeion sort to put the rightBlock and val in the exact position
//             //of th parentBlock [here curBlock] take a new child block and assign rightBlock to it
//
//             DataNode *newChildBlock = new DataNode();
//             newChildBlock = rightBlock;
//
//             //simple insertion sort to put val at the exact position of values[] in the parentBlock [here curBlock]
//
//
//             for (i = 0; i <= curBlock->node_num; i++) {
//                 if (val < curBlock->indexes[i]) {
//                     swap(curBlock->indexes[i], val);
//                     swap(curBlock->data[i], data);
//                 }
//             }
//
//             //after putting val number of nodes gets increase by one
//             curBlock->node_num++;
//
//             //simple insertNodeion sort to put rightBlock at the exact position
//             //of childBlock[] in the parentBlock [here curBlock]
//
//             for (i = 0; i < curBlock->node_num; i++) {
//                 if (newChildBlock->indexes[0] < curBlock->childBlock[i]->indexes[0]) {
//                     swap(curBlock->childBlock[i], newChildBlock);
//                 }
//             }
//             curBlock->childBlock[i] = newChildBlock;
//
//             //we reordered some blocks and pointers, so for the sake of safety
//             //all childBlocks' should have their parent updated
//             for (i = 0; curBlock->childBlock[i] != NULL; i++) {
//                 curBlock->childBlock[i]->parentBlock = curBlock;
//             }
//         }
//
//     }
//
//     void insert(Indexes index, DataType data) {
//         insertNode(rootBlock, index, data);
//     }
//
//     void del(int val) {
//         dataFound = false;
//         deleteNode(rootBlock, val, 0);
//     }
//
//     void insertNode(DataNode *curBlock, Indexes val, DataType data) {
//         // std::cout << "insert: " << data << std::endl;
//
//         for (int i = 0; i <= curBlock->node_num; i++) {
//             if (val < curBlock->indexes[i] && curBlock->childBlock[i] != NULL) {
//                 insertNode(curBlock->childBlock[i], val, data);
//                 if (curBlock->node_num == numberOfPointers)
//                     splitNonLeaf(curBlock);
//                 return;
//             } else if (val < curBlock->indexes[i] && curBlock->childBlock[i] == NULL) {
//                 swap(curBlock->indexes[i], val);
//                 swap(curBlock->data[i], data);
//                 //swap(curBlock->childBlock[i], newChildBlock);
//                 if (i == curBlock->node_num) {
//                     curBlock->node_num++;
//                     break;
//                 }
//             }
//         }
//
//         if (curBlock->node_num == numberOfPointers) {
//
//             splitLeaf(curBlock);
//         }
//     }
//
//
//     void redistributeBlock(DataNode *leftBlock, DataNode *rightBlock, bool isLeaf, int posOfLeftBlock,
//                            int whichOneisCurBlock) {
//         // std::cout << "redistributeBlock" << std::endl;
//         // std::cout << "pos: " << posOfLeftBlock << std::endl;
//         // std::cout << "which: " << whichOneisCurBlock << std::endl;
//         //re-distribution will affect the first indexes of the rightBlock, so remember it
//         //for later replacement of the copy of this indexes somewhere in ancestor Node
//         Indexes PrevRightFirstVal = rightBlock->indexes[0];
//
//
//         if (whichOneisCurBlock == 0) { //leftBlock is curBlock
//
//             //if the blocks are not leaf node
//             if (!isLeaf) {
//                 //bring down the indexes from which it is left child in parentBlock
//                 leftBlock->indexes[leftBlock->node_num] = leftBlock->parentBlock->indexes[posOfLeftBlock];
//                 leftBlock->data[leftBlock->node_num] = leftBlock->parentBlock->data[posOfLeftBlock];
//                 //the right child of newly added indexes should be the left child of first indexes of rightBlock
//                 leftBlock->childBlock[leftBlock->node_num + 1] = rightBlock->childBlock[0];
//                 //increase leftBlock's number of nodes by one
//                 leftBlock->node_num++;
//                 //send up a the first indexes of the rightBlock to the parentBlock
//                 leftBlock->parentBlock->indexes[posOfLeftBlock] = rightBlock->indexes[0];
//                 leftBlock->parentBlock->data[posOfLeftBlock] = rightBlock->data[0];
//                 //shift left by one in rightBlock
//
//                 memcpy(&rightBlock->indexes[0], &rightBlock->indexes[1], sizeof(Indexes) * (rightBlock->node_num + 1));
//                 memcpy(&rightBlock->data[0], &rightBlock->data[1], sizeof(DataType) * (rightBlock->node_num + 1));
//                 memcpy(&rightBlock->childBlock[0], &rightBlock->childBlock[1],
//                        sizeof(rootBlock) * (rightBlock->node_num + 1));
//                 rightBlock->node_num--;
//
//
//             } else {
//                 //borrow the first indexes of rightBlock to the last position of leftBlock
//                 leftBlock->indexes[leftBlock->node_num] = rightBlock->indexes[0];
//                 leftBlock->data[leftBlock->node_num] = rightBlock->data[0];
//                 leftBlock->node_num++;
//                 //shift by one node to left of the rightBlock
//                 memcpy(&rightBlock->indexes[0], &rightBlock->indexes[1], sizeof(Indexes) * (rightBlock->node_num + 1));
//                 memcpy(&rightBlock->data[0], &rightBlock->data[1], sizeof(DataType) * (rightBlock->node_num + 1));
//                 //decrease number of nodes by one
//                 rightBlock->node_num--;
//
//                 leftBlock->parentBlock->indexes[posOfLeftBlock] = rightBlock->indexes[0];
//                 leftBlock->parentBlock->data[posOfLeftBlock] = rightBlock->data[0];
//             }
//
//
//         } else { //rightBlock is curBlock
//
//             if (!isLeaf) {
//
//                 // //shift right by one in rightBlock so that first position becomes free
//                 // std::cout << "r0: " << rightBlock->indexes[0] << std::endl;
//                 // std::cout << "r1: " << rightBlock->indexes[1] << std::endl;
//                 //  std::cout << "right: " << std::endl;
//                 // for (int i = 0; i < rightBlock->node_num; i++) {
//                 //     std::cout << rightBlock->indexes[i] << std::endl;
//                 // }
//                 // memcpy(&rightBlock->indexes[1], &rightBlock->indexes[0], sizeof(Indexes)*(rightBlock->node_num+1));
//                 for (int i = rightBlock->node_num; i > 0; i--)
//                     rightBlock->indexes[i] = rightBlock->indexes[i - 1];
//                 for (int i = rightBlock->node_num; i > 0; i--)
//                     rightBlock->data[i] = rightBlock->data[i - 1];
//                 memcpy(&rightBlock->childBlock[1], &rightBlock->childBlock[0],
//                        sizeof(rootBlock) * (rightBlock->node_num + 1));
//
//
//                 //bring down the indexes from which it is left child in parentBlock to first pos of rightBlock
//                 rightBlock->indexes[0] = leftBlock->parentBlock->indexes[posOfLeftBlock];
//                 rightBlock->data[0] = leftBlock->parentBlock->data[posOfLeftBlock];
//                 rightBlock->childBlock[0] = leftBlock->childBlock[leftBlock->node_num];
//                 rightBlock->node_num++;
//
//                 //send up a the last indexes of the leftBlock to the parentBlock
//                 leftBlock->parentBlock->indexes[posOfLeftBlock] = leftBlock->indexes[leftBlock->node_num - 1];
//                 leftBlock->parentBlock->data[posOfLeftBlock] = leftBlock->data[leftBlock->node_num - 1];
//                 //erase the last element and pointer of leftBlock
//                 leftBlock->indexes[leftBlock->node_num - 1] = empty_index;
//                 // todo: handle data[LeftBlock->node_num-1]
//                 leftBlock->childBlock[leftBlock->node_num] = NULL;
//                 leftBlock->node_num--;
//
//             } else {
//
//                 //shift by one node to right of the rightBlock so that we can free the first position
//                 // memcpy(&rightBlock->indexes[1], &rightBlock->indexes[0], sizeof(Indexes)*(rightBlock->node_num+1));
//                 for (int i = rightBlock->node_num; i > 0; i--)
//                     rightBlock->indexes[i] = rightBlock->indexes[i - 1];
//                 for (int i = rightBlock->node_num; i > 0; i--)
//                     rightBlock->data[i] = rightBlock->data[i - 1];
//                 //borrow the last indexes of leftBlock to the first position of rightBlock
//                 rightBlock->indexes[0] = leftBlock->indexes[leftBlock->node_num - 1];
//                 rightBlock->data[0] = leftBlock->data[leftBlock->node_num - 1];
//                 //increase number of nodes by one
//                 rightBlock->node_num++;
//
//                 leftBlock->indexes[leftBlock->node_num - 1] = empty_index;
//                 // todo: handle data[LeftBlock->node_num-1]
//                 leftBlock->node_num--;
//
//                 leftBlock->parentBlock->indexes[posOfLeftBlock] = rightBlock->indexes[0];
//                 leftBlock->parentBlock->data[posOfLeftBlock] = rightBlock->data[0];
//             }
//         }
//     }
//
//     void mergeBlock(DataNode *leftBlock, DataNode *rightBlock, bool isLeaf, int posOfRightBlock) {
//
//         //cout << "leftBlock " << leftBlock->indexes[0] << " rightBlock " << rightBlock->indexes[0] << endl;
//         //cout << "size " << leftBlock->node_num << " size " << rightBlock->node_num << endl;
//         // std::cout << "mergeBlock" << std::endl;
//         if (!isLeaf) {
//
//             leftBlock->indexes[leftBlock->node_num] = leftBlock->parentBlock->indexes[posOfRightBlock - 1];
//             leftBlock->data[leftBlock->node_num] = leftBlock->parentBlock->data[posOfRightBlock - 1];
//             leftBlock->node_num++;
//         }
//
//         memcpy(&leftBlock->indexes[leftBlock->node_num], &rightBlock->indexes[0],
//                sizeof(Indexes) * (rightBlock->node_num + 1));
//         memcpy(&leftBlock->data[leftBlock->node_num], &rightBlock->data[0],
//                sizeof(DataType) * (rightBlock->node_num + 1));
//         memcpy(&leftBlock->childBlock[leftBlock->node_num], &rightBlock->childBlock[0],
//                sizeof(rootBlock) * (rightBlock->node_num + 1));
//
//
//         leftBlock->node_num += rightBlock->node_num;
//
//
//         // cout << "before: " << leftBlock->parentBlock->indexes[1] << endl;
//         memcpy(&leftBlock->parentBlock->indexes[posOfRightBlock - 1], &leftBlock->parentBlock->indexes[posOfRightBlock],
//                sizeof(Indexes) * (leftBlock->parentBlock->node_num + 1));
//         memcpy(&leftBlock->parentBlock->data[posOfRightBlock - 1], &leftBlock->parentBlock->data[posOfRightBlock],
//                sizeof(DataType) * (leftBlock->parentBlock->node_num + 1));
//         memcpy(&leftBlock->parentBlock->childBlock[posOfRightBlock],
//                &leftBlock->parentBlock->childBlock[posOfRightBlock + 1],
//                sizeof(rootBlock) * (leftBlock->parentBlock->node_num + 1));
//         // cout << "after merging " << leftBlock->parentBlock->childBlock[posOfRightBlock-2]->indexes[0] << " and ";// << leftBlock->parentBlock->childBlock[posOfRightBlock]->indexes[0] << endl;
//         leftBlock->parentBlock->node_num--;
//
//         //we reordered some blocks and pointers, so for the sake of safety
//         //all childBlocks' should have their parent updated
//         for (int i = 0; leftBlock->childBlock[i] != NULL; i++) {
//             leftBlock->childBlock[i]->parentBlock = leftBlock;
//         }
//
//
//     }
//
//
//     void deleteNode(DataNode *curBlock, Indexes val, int curBlockPosition) {
//
//         //to check if the current block is a leaf or not
//         bool isLeaf;
//         if (curBlock->childBlock[0] == NULL)
//             isLeaf = true;
//         else isLeaf = false;
//
//         //left most indexes could be changed due to merge or re-distribution later,
//         //so keep it to replace it's copy from it's ancestor
//         Indexes prevLeftMostVal = curBlock->indexes[0];
//         // DataType preLeftData = curBlock->data[0];
//
//
//         for (int i = 0; dataFound == false && i <= curBlock->node_num; i++) {
//             if (val < curBlock->indexes[i] && curBlock->childBlock[i] != NULL) {
//                 deleteNode(curBlock->childBlock[i], val, i);
//             }
//                 //if we could find the target indexes at any leafBlock then
//             else if (val == curBlock->indexes[i] && curBlock->childBlock[i] == NULL) {
//                 // std::cout << "del pos: " << i << std::endl;
//                 //delete the node by shifting all values and pointers  by one to the left
//                 memcpy(&curBlock->indexes[i], &curBlock->indexes[i + 1], sizeof(Indexes) * (curBlock->node_num + 1));
//                 memcpy(&curBlock->data[i], &curBlock->data[i + 1], sizeof(DataType) * (curBlock->node_num + 1));
//                 //decrease number of nodes by one
//                 curBlock->node_num--;
//                 dataFound = true;
//                 break;
//             }
//         }
//
//         //if the root is the only leaf
//         if (curBlock->parentBlock == NULL && curBlock->childBlock[0] == NULL) {
//             return;
//         }
//
//
//         //if the curBlock is rootBlock and it has one pointers only
//         if (curBlock->parentBlock == NULL && curBlock->childBlock[0] != NULL && curBlock->node_num == 0) {
//             rootBlock = curBlock->childBlock[0];
//             rootBlock->parentBlock = NULL;
//             return;
//         }
//
//
//         //now check if the curBlock has less than half of the number of maximum node
//         //cout << curBlockPosition << endl;
//         //if less than half we will try to re-distribute first
//
//         //cout << curBlock->childBlock[0]->indexes[0] << " "<< curBlockPosition << endl;
//         if (isLeaf && curBlock->parentBlock != NULL) {
//
//             if (curBlockPosition == 0) {
//                 DataNode *rightBlock = new DataNode();
//                 rightBlock = curBlock->parentBlock->childBlock[1];
//
//                 //if we the right one has more than half nodes of maximum capacity than re-distribute
//                 if (rightBlock != NULL && rightBlock->node_num > (numberOfPointers + 1) / 2) {
//
//                     redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
//                 }
//                     //else there is nothing to re-distribute, so we can merge them
//                 else if (rightBlock != NULL && curBlock->node_num + rightBlock->node_num < numberOfPointers) {
//
//                     mergeBlock(curBlock, rightBlock, isLeaf, 1);
//                 }
//             } else {
//
//
//                 DataNode *leftBlock = new DataNode();
//                 DataNode *rightBlock = new DataNode();
//
//
//                 leftBlock = curBlock->parentBlock->childBlock[curBlockPosition - 1];
//
//                 rightBlock = curBlock->parentBlock->childBlock[curBlockPosition + 1];
//
//
//                 //if we see that left one has more than half nodes of maximum capacity then try to re-distribute
//                 if (leftBlock != NULL && leftBlock->node_num > (numberOfPointers + 1) / 2) {
//                     redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition - 1, 1);
//                 } else if (rightBlock != NULL && rightBlock->node_num > (numberOfPointers + 1) / 2) {
//                     redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
//                 } else if (leftBlock != NULL && curBlock->node_num + leftBlock->node_num < numberOfPointers) {
//                     mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
//                 } else if (rightBlock != NULL && curBlock->node_num + rightBlock->node_num < numberOfPointers) {
//                     mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition + 1);
//                 }
//             }
//         } else if (!isLeaf && curBlock->parentBlock != NULL) {
//
//             if (curBlockPosition == 0) {
//                 DataNode *rightBlock = new DataNode();
//                 rightBlock = curBlock->parentBlock->childBlock[1];
//
//                 //if we see the right one has more than half nodes of maximum capacity than re-distribute
//                 if (rightBlock != NULL && rightBlock->node_num - 1 >= ceil((numberOfPointers - 1) / 2)) {
//                     redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
//                 }
//                     //else there is nothing to re-distribute, so we can merge them
//                 else if (rightBlock != NULL && curBlock->node_num + rightBlock->node_num < numberOfPointers - 1) {
//                     mergeBlock(curBlock, rightBlock, isLeaf, 1);
//                 }
//             }
//                 //for any other case we can safely take the left one to try for re-distribution
//             else {
//
//
//                 DataNode *leftBlock = new DataNode();
//                 DataNode *rightBlock = new DataNode();
//
//
//                 leftBlock = curBlock->parentBlock->childBlock[curBlockPosition - 1];
//
//                 rightBlock = curBlock->parentBlock->childBlock[curBlockPosition + 1];
//
//
//                 //if we see that left one has more than half nodes of maximum capacity then try to re-distribute
//                 if (leftBlock != NULL && leftBlock->node_num - 1 >= ceil((numberOfPointers - 1) / 2)) {
//                     redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition - 1, 1);
//                 } else if (rightBlock != NULL && rightBlock->node_num - 1 >= ceil((numberOfPointers - 1) / 2)) {
//                     redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
//                 }
//                     //else there is nothing to re-distribute, so we merge them
//
//                 else if (leftBlock != NULL && curBlock->node_num + leftBlock->node_num < numberOfPointers - 1) {
//                     mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
//                 } else if (rightBlock != NULL && curBlock->node_num + rightBlock->node_num < numberOfPointers - 1) {
//                     mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition + 1);
//                 }
//             }
//
//         }
//
//
//
//         //delete the duplicate if any in the ancestor Node
//         DataNode *tempBlock = new DataNode();
//         tempBlock = curBlock->parentBlock;
//         while (tempBlock != NULL) {
//             for (int i = 0; i < tempBlock->node_num; i++) {
//                 if (tempBlock->indexes[i] == prevLeftMostVal) {
//                     tempBlock->indexes[i] = curBlock->indexes[0];
//                     tempBlock->data[i] = curBlock->data[0];
//                     break;
//                 }
//             }
//             tempBlock = tempBlock->parentBlock;
//         }
//
//     }
//
//     void print() {
//         _print({rootBlock});
//     }
//
//     void _print(vector<DataNode *> Blocks) {
//         vector<DataNode *> newBlocks;
//         for (int i = 0; i < Blocks.size(); i++) { //for every block
//             DataNode *curBlock = Blocks[i];
//
//             cout << "[|";
//             int j;
//             for (j = 0; j < curBlock->node_num; j++) {
//                 //traverse the childBlocks, print values and save all the childBlocks
//                 cout << curBlock->indexes[j] << "(" << curBlock->data[j] << ")" << "|";
//                 if (curBlock->childBlock[j] != NULL)
//                     newBlocks.push_back(curBlock->childBlock[j]);
//             }
//
//             if (curBlock->indexes[j] == empty_index && curBlock->childBlock[j] != NULL)
//                 newBlocks.push_back(curBlock->childBlock[j]);
//
//             cout << "]  ";
//         }
//
//         if (newBlocks.size() == 0) {
//             //if there is no childBlock block left to send out then just the end of the recursion
//             puts("");
//             puts("");
//             Blocks.clear();
//             //exit(0);
//         } else {
//             //else send the childBlocks to the recursion to continue to the more depth
//             puts("");
//             puts("");
//             Blocks.clear();
//             // std::cout << "----------------1111" << std::endl;
//             _print(newBlocks);
//         }
//     }
//
//     vector<DataNode *> preorder_traversal(DataNode* node){
//         if(!node)
//             return {};
//         bool is_leaf = true;
//         for (int i = 0; i < node->node_num+1; i++) {
//             if(node->childBlock[i] != NULL){
//                 is_leaf = false;
//                 break;
//             }
//         }
//
//         if(is_leaf) {
//             return {node};
//         }else{
//             vector<DataNode *> leafs;
//             for(int i = 0; i < node->node_num+1; i++){
//                 if(node->childBlock[i] != NULL){
//                    vector<DataNode *> tmp = preorder_traversal(node->childBlock[i]);
//                    leafs.insert(leafs.end(), tmp.begin(), tmp.end());
//                 }
//             }
//             return leafs;
//         }
//     }
//
//     void save_to_file() {
//         ostream ss(cout.rdbuf());
//         vector<DataNode *> res = preorder_traversal(rootBlock);
//         for (int i = 0; i < res.size(); i++) {
//             for(int j = 0; j < res[i]->node_num; j++){
//                 // 第一行为索引
//                 ss << res[i]->indexes[j] << endl;
//                 // 第二行为值
//                 ss << res[i]->data[j] << endl;
//             }
//         }
//         ss << endl;
//     }
//
// };
//
//
// int main() {
//     int num[50];// = {1,4,7,10,17,21,31,25,19,20,28,42};
//     // int num[] = {5,10,15,20,25,28,30,50,55,60,65,70,75,80,85,90,95};
//
//
//     // printf("Pointers: ");
//     // scanf("%d", &numberOfPointers);
//     int numberOfPointers = 5;
//     FILE *p;
//     p = fopen("input.txt", "r");
//     // freopen("output.txt", "w", stdout);
//     DBBPlusTree<int> b(5);
//
//
//     using DataNode = Node<int>;
//     vector<DataNode *> Blocks;
//
//
//     int ch;
//     int i = 0;
//     int totalValues = 0;
//     //input from file
//     printf("1.Insert a value\n2.Print the tree\n3.Delete a value\n");
//     while (fscanf(p, "%d", &ch) != EOF) {
//
//         if (ch == 1) {
//             fscanf(p, "%d", &num[i]);
//             printf("**** Insert %d ****\n\n", num[i]);
//             // insertNode(rootBlock, num[i]);
//             Indexes index;
//             index.push(num[i]);
//             index.push("a");
//             b.insert(index, i + 1);
//             i++;
//             totalValues++;
//
//         } else if (ch == 2) {
//             Blocks.clear();
//             Blocks.push_back(b.get_root());
//             // print(Blocks);
//             puts("");
//             b.save_to_file();
//             b.print();
//
//         } else if (ch == 3) {
//             int val;
//             fscanf(p, "%d", &val);
//             if (totalValues == 0) {
//                 printf("Sorry! There is no more data to be deleted!!");
//                 continue;
//
//             }
//             printf("---- Delete %d ----\n\n", val);
//             // dataFound = false;
//             // deleteNode(rootBlock, val, 0);
//             b.del(val);
//
//             totalValues--;
//         }
//     }
//     //input manually
//     //  while(scanf("%d", &ch)!=EOF){
//     //
//     //
//     //     if(ch==1){
//     //         scanf("%d", &num[i]);
//     //         printf("**** Insert %d ****\n\n", num[i]);
//     //         insertNode(rootBlock, num[i]);
//     //         i++;
//     //         totalValues++;
//     //
//     //     }else if(ch==2){
//     //         Blocks.clear();
//     //         Blocks.push_back(rootBlock);
//     //         print(Blocks);
//     //         puts("");
//     //
//     //     }else if(ch==3) {
//     //         int val;
//     //         scanf("%d", &val);
//     //         if(totalValues==0) {
//     //             printf("Sorry! There is no more data to be deleted!!");
//     //             continue;
//     //
//     //         }
//     //         printf("---- Delete %d ----\n\n", val);
//     //         dataFound = false;
//     //         deleteNode(rootBlock, val, 0);
//     //         totalValues--;
//     //     }
//     // }
//     //
//     //
//     // return 0;
// }
// #include "sql_gram.tab.h"
// #include "gram.h"
// int main(){
//     GramTree* root;
//     GramTree* temp;
// 	root=new GramTree();
//     root->setType(GramTree::GRAM_ROOT);
//     temp=new GramTree();
//     temp->setType(GramTree::GRAM_TEMP);
// 	while(yyparse()!=0){
// 	    root->showTree();
// 	    root=new GramTree();
//         root->setType(GramTree::GRAM_ROOT);
//         temp=new GramTree();
//         temp->setType(GramTree::GRAM_TEMP);
//         p=NULL;
// 	}
// }