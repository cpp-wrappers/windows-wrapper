#include "../../include/winapi/file.hpp"

#include <exception>
#include <stdexcept>
#include <system_error>

using namespace windows;

int main(int argc, char* argv[]) {
    file in = create_file(
        argv[0],
        {access::read},
        {share::read},
        disposition::open_existing,
        {file_attrib::normal}
    );

    file out = create_file(
        argv[1],
        {access::write},
        {},
        disposition::always_create,
        {file_attrib::normal}
    );

    #define BUF_SIZE 256
    char buf[BUF_SIZE];
    unsigned long read;

    while((read = in.read(buf, BUF_SIZE)))
        if(read != out.write(buf, read))
            throw std::runtime_error{"fatal write error"};
}