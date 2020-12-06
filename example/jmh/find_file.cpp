#include "../../include/winapi/file_search.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace windows;

int main(int argc, char* argv[]) {
    std::wstring arg(std::strlen(argv[1]), 0);
    std::mbstowcs(arg.data(), argv[1], arg.length());

    for(auto str : file_search_iterator(arg))
        std::wcout << str << std::endl;
    return 0;
}