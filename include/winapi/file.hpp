#pragma once

#include "handle.hpp"
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include "internal.hpp"
#include <system_error>
#include "error.hpp"

namespace windows {

namespace internal {
    void* create_file(const wchar_t* str, int access, int share_mode, int creation_disposition, int flags_and_attrs);
    bool read_file(void* h, void* buf, int bytes_to_read, unsigned long* bytes_read);
    bool write_file(void* h, void* buf, int bytes_to_write, unsigned long* bytes_written);
    void* get_std_handle(int h);
    int get_current_directory(int len, wchar_t* buf);
}

enum class access : unsigned { read = 0x80000000, write = 0x40000000 };

enum class share : unsigned { deletion = 4, read = 1, write = 2 };

enum class disposition : unsigned {
    always_create = 2,
    create_new = 1,
    always_open = 4,
    open_existing = 3,
    truncate_existing = 5
};

enum class file_attrib : unsigned {
    archive = 0x20,
    encrypted = 0x4000,
    hidden = 0x2,
    normal = 0x80,
    offline = 0x1000,
    readonly = 0x1,
    system = 0x4,
    temporary = 0x100
};

inline unsigned long read(const handle& h, auto* buf, int len) {
    unsigned long read;
    bool success = internal::read_file(h.raw(), buf, sizeof(decltype(*buf))*len, &read);
    if(!success) throw error { "cannot read file"};
    return read;
}

inline unsigned long write(const handle& h, auto* buf, int len) {
    unsigned long write;
    bool success = internal::write_file(h.raw(), buf, sizeof(decltype(*buf))*len, &write);
    if(!success) throw error {"cannot write file"};
    return write;
}


template<class HandleT>
class basic_file {
    HandleT h;

public:
    basic_file(void* raw_handle) : h{raw_handle}{}

    unsigned long read(void* buf, int bytes) {
        return read(h, buf, bytes);
    }

    unsigned long write(void* buf, int bytes) {
        return write(h, buf, bytes);
    }

    handle handle() {
        return {h.raw()};
    }
};

using file = basic_file<managed_handle>;

inline file create_file(
    std::wstring name,
    std::initializer_list<access> access_mode,
    std::initializer_list<share> sm,
    disposition d,
    std::initializer_list<file_attrib> fa
) {
    void* h = internal::create_file(
        name.c_str(),
        internal::make_bit_field(access_mode),
        internal::make_bit_field(sm),
        (unsigned) d,
        internal::make_bit_field(fa)
    );

    if(h == (void*)(long long)-1)
        throw error {"cannot open file"};

    return {h};
}

inline file open_existing_file_for_reading(std::wstring name) {
    return create_file(name, {access::read}, {share::read}, disposition::open_existing, {file_attrib::normal});
}

inline file create_file_for_writing(std::wstring name) {
    return create_file(name, {access::write}, {}, disposition::always_create, {file_attrib::normal});
}

enum class std_handle_type {
    input = -10, output = -11, error = -12
};

inline handle get_std_handle(std_handle_type std_h) {
    void* h = internal::get_std_handle(int(std_h));

    if(h == (void*)(long long)-1)
        throw error { "cannot get std handler" };

    return {h};
}

inline handle get_std_input_handle() { return get_std_handle(std_handle_type::input); }
inline handle get_std_output_handle() { return get_std_handle(std_handle_type::output); }
inline handle get_std_error_handle() { return get_std_handle(std_handle_type::error); }

inline std::wstring get_current_directory() {
    int size = internal::get_current_directory(0, nullptr);
    if(size == 0)
        throw error{"cannot retrieve current directory path size"};
    
    std::wstring res(size, 0);
    if(internal::get_current_directory(res.size(), res.data()) == 0)
        throw error{"cannot get current directory"};

    return std::move(res);
}

}