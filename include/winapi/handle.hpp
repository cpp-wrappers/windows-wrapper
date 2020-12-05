#pragma once

#include <utility>
#include "error.hpp"

namespace windows {

namespace internal {
    bool close_handle(void* h);
}

struct handle {
protected:
    void* raw_handle;

public:
    handle(void* h) : raw_handle{h} {}

    void* raw() const { return raw_handle; }
};

struct managed_handle : handle {
    using handle::handle;

    ~managed_handle() noexcept(false) {
        if(!internal::close_handle(std::exchange(raw_handle, nullptr)))
            throw error{ "cannot close handle" };
    }
};

}