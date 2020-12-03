#pragma once

#include <initializer_list>

namespace windows {

namespace internal {

template<class T>
unsigned make_bit_field(std::initializer_list<T> l) {
    unsigned result = 0;
    for(auto e : l) result |= (unsigned) e;
    return result;
}

}

}