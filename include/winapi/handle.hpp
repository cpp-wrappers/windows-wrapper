#pragma once

#include <utility>
#include <system_error>
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
        internal::close_handle(std::exchange(raw_handle, nullptr));

        std::system_error{
            std::error_code{internal::get_last_error(), std::system_category()},
            "Cannot close handle"
        };
    }

    void* raw() {
        return raw_handle;
    }
};

}