#pragma once

#include <enum_flags.hpp>

namespace win {

	enum class file_access : unsigned {
		read = 0x80000000,
		write = 0x40000000
	};

	using file_accesses = enum_flags<win::file_access>;

} // win