#ifndef DBMS_INDEX_H
#define DBMS_INDEX_H

#include<bits/stdc++.h>
// #include "boost/variant.hpp"
// #include <boost/any.hpp>
// #include "file.h"
#include <streambuf>
#include "col_types/col_type_interface.h"

class Index : public std::vector<ColTypeInterface*> {

public:
    Index();
    friend bool operator<(const Index &i1, const Index &i2);

    friend bool operator==(const Index &i1, const Index &i2);

    friend bool operator>(const Index &i1, const Index &i2);

    friend std::ostream& operator<<(std::ostream& os, Index const& data);
};


#endif //DBMS_INDEX_H
