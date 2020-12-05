#include "../include/winapi/file.hpp"

#include <handleapi.h>
#include <processenv.h>
#include <windows.h>

using namespace windows;

void* internal::create_file(
    const wchar_t* str,
    int access,
    int share_mode,
    int creation_disposition,
    int flags_and_attrs
) {
    return CreateFileW(str, access, share_mode, nullptr, creation_disposition, flags_and_attrs, nullptr);
}

bool internal::read_file(void* h, void* buf, int bytes_to_read, unsigned long* bytes_read) {
    return ReadFile(h, buf, bytes_to_read, bytes_read, nullptr);
}

bool internal::write_file(void* h, void* buf, int bytes_to_write, unsigned long* bytes_written) {
    return WriteFile(h, buf, bytes_to_write, bytes_written, nullptr);
}

void* internal::get_std_handle(int h) {
    return GetStdHandle(h);
}

int internal::get_current_directory(int len, wchar_t *buf) {
    return GetCurrentDirectoryW(len, buf);
}