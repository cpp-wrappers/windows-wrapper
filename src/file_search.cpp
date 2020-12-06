//#define _MAC
#include "../include/winapi/file_search.hpp"
#include <windows.h>
using namespace windows;

static inline void convert(_WIN32_FIND_DATAW& fdw, internal::find_data& fd) {
    fd.file_attribs = fdw.dwFileAttributes;
    fd.file_name = fdw.cFileName;
}

void* internal::find_first_file(const wchar_t* file_name, find_data& fd) {
    _WIN32_FIND_DATAW fdw{};

    HANDLE h = FindFirstFileW(file_name, &fdw);

    convert(fdw, fd);

    return h;
}

bool internal::find_next_file(void* handle, find_data& fd) {
    _WIN32_FIND_DATAW fdw;

    bool res = FindNextFileW(handle, &fdw);

    convert(fdw, fd);

    return res;
}

bool internal::find_close(void *h) {
    return FindClose(h);
}
