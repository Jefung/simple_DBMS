#ifndef DBMS_INT_H
#define DBMS_INT_H

#include "col_type_interface.h"
class Int: public ColTypeInterface {
public:
    int data;
    Int(int data) : data(data) {};

protected:
    virtual bool less(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual bool greater(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual bool equal(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual void print(std::ostream &ss) const;
};


#endif //DBMS_INT_H
