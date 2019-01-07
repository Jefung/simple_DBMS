#include "col_type_interface.h"

bool operator<(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.less(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool operator>(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.greater(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool operator==(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.equal(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool operator>=(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.greater_or_equal(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool operator<=(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.less_or_equal(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool operator!=(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    return i1.not_equal(const_cast<ColTypeInterface *>(&i1), const_cast<ColTypeInterface *>(&i2));
}

bool ColTypeInterface::not_equal(ColTypeInterface *p1, ColTypeInterface *p2) const {
    return !equal(p1, p2);
}

bool ColTypeInterface::greater_or_equal(ColTypeInterface *p1, ColTypeInterface *p2) const {
    return greater(p1, p2) || equal(p1, p2);
}

bool ColTypeInterface::less_or_equal(ColTypeInterface *p1, ColTypeInterface *p2) const {
    return less(p1, p2) || equal(p1, p2);
}

