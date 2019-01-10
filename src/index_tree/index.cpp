#include "index.h"

bool operator<(const Index &i1, const Index &i2) {
    unsigned long size = i1.size() > i2.size() ? i2.size() : i1.size();
    for (int i = 0; i < size; i++) {
        // todo: 支持不同类型比较?
        if (typeid(*i1[i]) != typeid(*i2[i]))
            throw "the column type must be same";
        if (*i1[i] > *i2[i])
            return false;
    }
    if(*i1[size-1] == *i2[size-1])
        return false;
        // throw "index values can't be same";
    return true;
}

bool operator==(const Index &i1, const Index &i2) {
    unsigned long size = i1.size() > i2.size() ? i2.size() : i1.size();
    for (int i = 0; i < size; i++) {
        // todo: 支持不同类型比较?
        if (typeid(*i1[i]) != typeid(*i2[i]))
            throw "the column type must be same";
        if (*i1[i] != *i2[i])
            return false;
    }
    return true;
}

bool operator>(const Index &i1, const Index &i2) {
    unsigned long size = i1.size() > i2.size() ? i2.size() : i1.size();
    for (int i = 0; i < size; i++) {
        // todo: 支持不同类型比较?
        // std::cout << typeid(*i1[i]).name() << std::endl;
        // std::cout << typeid(*i2[i]).name() << std::endl;
        if (typeid(*i1[i]) != typeid(*i2[i])){
            std::cout << "the column type must be same" << std::endl;
            throw "the column type must be same";
        }
        if (*i1[i] < *i2[i])
            return false;
    }
    if(*i1[size-1] == *i2[size-1]){
        // std::cout << "index values can't be same" << std::endl;
        // throw "index values can't be same";
        return false;
    }
    return true;
}

Index::Index() {

}

std::ostream &operator<<(std::ostream &os, const Index &data){
    for(int i = 0; i < data.size(); i++){
        os << *data[i];
    }
    return os;
}

bool operator>=(const Index &i1, const Index &i2){
    return i1 > i2 || i1 == i2;
}

bool operator<=(const Index &i1, const Index &i2){
    return i1 < i2 || i1 == i2;
}
