#include "../../include/winapi/file.hpp"

int main(int argc, char* argv[]) {
    auto wd = windows::get_current_directory();
    windows::write(windows::get_std_output_handle(), wd.data(), wd.size());
}