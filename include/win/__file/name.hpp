#pragma once

#include <c_string.hpp>

namespace win {

	struct file_name : c_string<wchar_t> {};

	using path = win::file_name;

} // win