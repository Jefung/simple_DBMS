#ifndef DBMS_COL_TYPE_INTERFACE_H
#define DBMS_COL_TYPE_INTERFACE_H

#include <iostream>

class ColTypeInterface{
public:

    friend bool operator<(const ColTypeInterface &i1, const ColTypeInterface &i2);

    friend bool operator>(const ColTypeInterface &i1, const ColTypeInterface &i2);

    friend bool operator==(const ColTypeInterface &i1, const ColTypeInterface &i2);

    friend bool operator>=(const ColTypeInterface &i1, const ColTypeInterface &i2);


    friend bool operator<=(const ColTypeInterface &i1, const ColTypeInterface &i2);

    friend bool operator!=(const ColTypeInterface &i1, const ColTypeInterface &i2);

    friend std::ostream &operator<<(std::ostream &os, ColTypeInterface const &data){
        data.print(os);
        return os;
    }

protected:
    virtual void print(std::ostream &str) const = 0;

    virtual bool less(ColTypeInterface *p1, ColTypeInterface *p2) const = 0;

    virtual bool greater(ColTypeInterface *p1, ColTypeInterface *p2) const = 0;

    virtual bool equal(ColTypeInterface *p1, ColTypeInterface *p2) const = 0;

    virtual bool not_equal(ColTypeInterface *p1, ColTypeInterface *p2) const;

    virtual bool greater_or_equal(ColTypeInterface *p1, ColTypeInterface *p2) const;

    virtual bool less_or_equal(ColTypeInterface *p1, ColTypeInterface *p2) const;


};


#endif //DBMS_COL_TYPE_INTERFACE_H
