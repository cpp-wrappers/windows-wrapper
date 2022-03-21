#pragma once

#include <core/flag_enum.hpp>

namespace win {

	enum class file_access : unsigned {
		read = 0x80000000,
		write = 0x40000000
	};

	using file_accesses = flag_enum<win::file_access>;

} // win