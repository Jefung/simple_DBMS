#ifndef DBMS_STRING_H
#define DBMS_STRING_H

#include "col_type_interface.h"
#include <iostream>

class String : public ColTypeInterface {
public:
    std::string data;
    String(std::string data) : data(data) {};


protected:
    virtual bool less(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual bool greater(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual bool equal(ColTypeInterface* p1, ColTypeInterface* p2) const;
    virtual void print(std::ostream &ss) const;
};


#endif //DBMS_STRING_H
