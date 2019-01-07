#include "string.h"

bool String::less(const ColTypeInterface* obj1, const ColTypeInterface* obj2) const {
    // ColTypeInterface t1;
    ColTypeInterface* c1 = const_cast<ColTypeInterface*> (obj1);
    String* s1 = dynamic_cast<String* >(c1);


    ColTypeInterface* c2 = const_cast<ColTypeInterface*> (obj2);
    String* s2 = dynamic_cast<String* >(c2);
    // std::cout << "String less" << std::endl;
    // return true;
    return s1->data < s2->data;
}
