#pragma once

#include <c_string.hpp>

namespace win {

	struct file_name : c_string<c_string_type::unknown_size, wchar_t> {};

	using path = win::file_name;

} // win