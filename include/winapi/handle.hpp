#pragma once

#include <utility>
#include "error.hpp"

namespace windows {

struct handle;

namespace internal {
    static inline void* invalid_handle = (void*)(long long) -1;

    inline handle create_handle(void* raw);
    inline void* raw(const handle& h);
    bool close_handle(void* h);
}

struct handle {
    friend inline void* internal::raw(const handle&);
    friend inline handle internal::create_handle(void* raw);

protected:
    void* raw = internal::invalid_handle;
    handle(void* h) : raw{h} {}
public:
    handle(const handle&) = delete;
    handle& operator=(const handle&) = delete;

    handle(handle&& r) : raw{ std::exchange(r.raw, nullptr) } {}
    handle& operator=(handle&& r) { std::exchange(r.raw, nullptr); return *this; }
};

inline handle internal::create_handle(void* raw) {
    return {raw};
}

inline void* internal::raw(const handle& h) {
    return (void*)h.raw;
}

class handle_with_generic_close : public handle {
protected:
    using handle::handle;
public:
    ~handle_with_generic_close() noexcept(false) {
        if(raw != internal::invalid_handle && !internal::close_handle(std::exchange(raw, internal::invalid_handle)))
            throw error{ "cannot close handle" };
    }
};

}