#pragma once

#include <utility>
#include "error.hpp"

namespace windows {

namespace internal {
    bool close_handle(void* h);
}

class handle {
    void* raw_handle;

public:
    handle(void* h) : raw_handle{h} {}

    ~handle() noexcept(false) {
        if(!internal::close_handle(std::exchange(raw_handle, nullptr)))
            throw error{ "cannot close handle" };
    }

    void* raw() { return raw_handle; }
};

}