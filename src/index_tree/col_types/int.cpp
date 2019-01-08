#include "int.h"
bool Int::less(ColTypeInterface* p1, ColTypeInterface* p2) const {
    Int* s1 = dynamic_cast<Int* >(p1);
    Int* s2 = dynamic_cast<Int* >(p2);
    return s1->data < s2->data;
}

bool Int::greater(ColTypeInterface *p1, ColTypeInterface *p2) const {
    Int* s1 = dynamic_cast<Int* >(p1);
    Int* s2 = dynamic_cast<Int* >(p2);
    return s1->data > s2->data;
}

bool Int::equal(ColTypeInterface *p1, ColTypeInterface *p2) const {
    Int* s1 = dynamic_cast<Int* >(p1);
    Int* s2 = dynamic_cast<Int* >(p2);
    return s1->data == s2->data;
}

void Int::print(std::ostream &os) const{
   os << data;
}
