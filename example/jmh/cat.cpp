#include "../../include/winapi/file.hpp"
#include <array>

using namespace windows;

void cat(const handle& in, const handle& out) {
    std::array<wchar_t, 256> buf;

    while(unsigned long read = windows::read(in, buf.data(), buf.size()))
        if(read != write(out, buf.data(), read))
            throw std::runtime_error{ "fatal write error" };
}

int wmain(int argc, wchar_t* argv[]) {
    auto out = get_std_output_handle();

    if(argc == 1)
        cat(get_std_input_handle(), out);
    else {
        for(int i = 1; i < argc; i++)
            cat(open_existing_file_for_reading(argv[i]), out);
    }
}