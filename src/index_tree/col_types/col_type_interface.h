#ifndef DBMS_COL_TYPE_INTERFACE_H
#define DBMS_COL_TYPE_INTERFACE_H


class ColTypeInterface {
public:
    virtual void t() = 0;
    friend bool operator<(const ColTypeInterface &i1, const ColTypeInterface &i2);
protected:
    virtual bool less(const ColTypeInterface* obj1, const ColTypeInterface* obj2) const = 0;

    // virtual bool greater(const ColTypeInterface &obj1, const ColTypeInterface &obj2) = 0;

    // virtual bool equal(const ColTypeInterface &obj1, const ColTypeInterface &obj2) = 0;

};


#endif //DBMS_COL_TYPE_INTERFACE_H
