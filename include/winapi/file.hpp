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
    void* create_file(std::string str, int access, int share_mode, int creation_disposition, int flags_and_attrs);
    bool read_file(void* h, void* buf, int bytes_to_read, unsigned long* bytes_read);
    bool write_file(void* h, void* buf, int bytes_to_write, unsigned long* bytes_written);
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

class file;


file create_file(
    std::string name,
    std::initializer_list<access> access_mode,
    std::initializer_list<share> sm,
    disposition d,
    std::initializer_list<file_attrib> fa
);

class file {
    handle h;

    friend file create_file(
        std::string name,
        std::initializer_list<access> access_mode,
        std::initializer_list<share> sm,
        disposition d,
        std::initializer_list<file_attrib> fa
    );

    file(void* raw_handle) : h{raw_handle}{}
public:

    unsigned long read(void* buf, int bytes) {
        unsigned long read;
        bool success = internal::read_file(h.raw(), buf, bytes, &read);
        if(!success) throw error { "cannot read file"};
        return read;
    }

    unsigned long write(void* buf, int bytes) {
        unsigned long write;
        bool success = internal::write_file(h.raw(), buf, bytes, &write);
        if(!success) throw error {"cannot write file"};
        return write;
    }
};

inline file create_file(
    std::string name,
    std::initializer_list<access> access_mode,
    std::initializer_list<share> sm,
    disposition d,
    std::initializer_list<file_attrib> fa
) {
    void* h = internal::create_file(
        name,
        internal::make_bit_field(access_mode),
        internal::make_bit_field(sm),
        (unsigned) d,
        internal::make_bit_field(fa)
    );

    if(h == (void*)(long long)-1)
        throw error {"cannot open file '" + name + "'"};

    return {h};
}

inline file open_existing_file_for_reading(std::string name) {
    return create_file(name, {access::read}, {share::read}, disposition::open_existing, {file_attrib::normal});
}

inline file create_file_for_writing(std::string name) {
    return create_file(name, {access::write}, {}, disposition::always_create, {file_attrib::normal});
}

}