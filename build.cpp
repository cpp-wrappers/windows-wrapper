#include "cxx_exec/ext/static_lib"

string_view name() { return "winapi-wrapper"; }

vector<path> sources() { return {"src/file.cpp", "src/handle.cpp", "src/error.cpp"}; }