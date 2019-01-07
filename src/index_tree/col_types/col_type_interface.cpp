#include <iostream>
#include "col_type_interface.h"

bool operator<(const ColTypeInterface &i1, const ColTypeInterface &i2) {
    std::cout << "friend <" << std::endl;
    return i1.less(&i1,&i2);
}
