#pragma once

#include "handle.hpp"
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include "internal.hpp"
#include <system_error>
#include "error.hpp"
#include "cxx_util/flags.hpp"

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

inline unsigned long read(const handle& h, std::byte* buf, int bytes) {
    unsigned long read;
    bool success = internal::read_file(internal::raw(h), buf, bytes, &read);
    if(!success) throw error { "cannot read file"};
    return read;
}

inline unsigned long write(const handle& h, std::byte* buf, int bytes) {
    unsigned long write;
    bool success = internal::write_file(internal::raw(h), buf, bytes, &write);
    if(!success) throw error {"cannot write file"};
    return write;
}

class file_handle : public kernel_object_handle {

public:
    file_handle(void* raw) : kernel_object_handle(raw) {}

    unsigned long read(std::byte* buf, int bytes) {
        return windows::read(*this, buf, bytes);
    }

    unsigned long write(std::byte* buf, int bytes) {
        return windows::write(*this, buf, bytes);
    }
};

inline file_handle create_file(
    std::wstring name,
    util::flags<access> access_mode,
    util::flags<share> sm,
    disposition d,
    util::flags<file_attrib> fa
) {
    void* h = internal::create_file(
        name.c_str(),
        access_mode.to<int>(),
        sm.to<int>(),
        (unsigned) d,
        fa.to<int>()
    );

    if(h == internal::invalid_handle)
        throw error {"cannot open file"};

    return {h};
}

inline file_handle open_existing_file_for_reading(std::wstring name) {
    return create_file(name, {access::read}, {share::read}, disposition::open_existing, {file_attrib::normal});
}

inline file_handle create_file_for_writing(std::wstring name) {
    return create_file(name, {access::write}, {}, disposition::always_create, {file_attrib::normal});
}

enum class std_handle_type {
    input = -10, output = -11, error = -12
};

inline handle get_std_handle(std_handle_type std_h) {
    void* h = internal::get_std_handle(int(std_h));

    if(h == internal::invalid_handle)
        throw error { "cannot get std handler" };

    return internal::create_handle(h);
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