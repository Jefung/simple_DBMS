#include "string.h"

bool String::less(ColTypeInterface* p1, ColTypeInterface* p2) const {
    String* s1 = dynamic_cast<String* >(p1);
    String* s2 = dynamic_cast<String* >(p2);
    return s1->data < s2->data;
}

bool String::greater(ColTypeInterface *p1, ColTypeInterface *p2) const {
    String* s1 = dynamic_cast<String* >(p1);
    String* s2 = dynamic_cast<String* >(p2);
    return s1->data > s2->data;
}

bool String::equal(ColTypeInterface *p1, ColTypeInterface *p2) const {
    String* s1 = dynamic_cast<String* >(p1);
    String* s2 = dynamic_cast<String* >(p2);
    return s1->data == s2->data;
}

void String::print(std::ostream &ss) const{
    ss << data;
}
