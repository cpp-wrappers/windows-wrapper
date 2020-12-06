#include "../../include/winapi/file.hpp"
#include <array>
#include <cstddef>
#include <cstring>

using namespace windows;

int main(int argc, char* argv[]) {
    std::wstring v1(std::strlen(argv[1]), 0);
    std::wstring v2(std::strlen(argv[2]), 0);

    mbstowcs(v1.data(), argv[1], v1.length());
    mbstowcs(v2.data(), argv[2], v2.length());

    auto in{open_existing_file_for_reading(L"cp.cpp")};
    auto out{create_file_for_writing(L"cp2.cpp")};

    std::array<std::byte, 256> buf;

    while(unsigned long read = in.read(buf.data(), buf.size()))
        if(read != out.write(buf.data(), read))
            throw std::runtime_error{ "fatal write error" };
}