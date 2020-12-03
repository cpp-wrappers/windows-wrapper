#include "../include/winapi/handle.hpp"
#include <handleapi.h>
#include <windows.h>
#include <system_error>
#include "../include/winapi/error.hpp"

using namespace windows;

bool internal::close_handle(void *h) {
    return CloseHandle(h);
}