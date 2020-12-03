#include "../include/winapi/error.hpp"
#include <errhandlingapi.h>

int windows::internal::get_last_error() {
    return GetLastError();
}