#include "cxx_exec/ext/static_lib"
#include <cxx_exec/ext/on_startup.hpp>

string_view name() { return "winapi-wrapper"; }

vector<path> sources() { return {"src/file.cpp", "src/handle.cpp", "src/error.cpp"}; }

on_startup set_std() {
    cc.std("c++20");
}