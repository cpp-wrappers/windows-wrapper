#pragma once

#include "handle.hpp"
#include <filesystem>
#include <string_view>

namespace windows {

namespace internal {
    void* load_library(const wchar_t* lib_file_name);
    void free_library(void* handle);
    void* get_proc_address(void* module, const char* proc_name);
}

class module_handle;
module_handle load_library(const std::filesystem::path& path);

struct module_handle : public handle {
protected:
    using handle::handle;
    friend module_handle load_library(const std::filesystem::path& path);

public:
    ~module_handle() {
        internal::free_library(raw);
    }

    template<class Func>
    Func* get_proc_address(std::string proc_name) {
        return (Func*) internal::get_proc_address(raw, proc_name.c_str());
    }
};

inline module_handle load_library(const std::filesystem::path& path) {
    return {internal::load_library(path.wstring().c_str())};
}

}