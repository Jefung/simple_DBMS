#ifndef DBMS_STRING_H
#define DBMS_STRING_H

#include "col_type_interface.h"
#include <iostream>

class String : public ColTypeInterface {
private:
public:
    std::string data;
    String(std::string data) : data(data) {};

    virtual void t() {
        std::cout << "String" << std::endl;
    }

protected:
    virtual bool less(const ColTypeInterface* obj1, const ColTypeInterface* obj2) const;
};


#endif //DBMS_STRING_H
