#include "../../include/winapi/file.hpp"
#include <array>

using namespace windows;

int main(int argc, char* argv[]) {
    file in = open_existing_file_for_reading(argv[1]);
    file out = create_file_for_writing(argv[2]);

    std::array<char, 256> buf;

    while(unsigned long read = in.read(buf.data(), buf.size()))
        if(read != out.write(buf.data(), read))
            throw std::runtime_error{ "fatal write error" };
}