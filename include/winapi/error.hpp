#pragma once

#include <system_error>

namespace windows {

namespace internal {
    int get_last_error();
}

struct error : std::system_error {
    using std::system_error::system_error;

    error(std::string message)
    : std::system_error(
        std::error_code { internal::get_last_error(), std::system_category()},
        message
    ) { }
};

}