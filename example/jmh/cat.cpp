#include "../../include/winapi/file.hpp"
#include <array>

using namespace windows;

void cat(const handle& in, const handle& out) {
    std::array<char, 256> buf;

    while(unsigned long read = windows::read(in, buf.data(), buf.size()))
        if(read != write(out, buf.data(), read))
            throw std::runtime_error{ "fatal write error" };
}

int main(int argc, char* argv[]) {
    auto out = get_std_output_handle();

    if(argc == 1)
        cat(get_std_input_handle(), out);
    else {
        for(int i = 1; i < argc; i++)
            cat(open_existing_file_for_reading(argv[i]).handle(), out);
    }
}