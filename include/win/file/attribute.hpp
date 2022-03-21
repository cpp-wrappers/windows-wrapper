#pragma once

#include <core/flag_enum.hpp>

namespace win {

	enum class file_attribute {
		archive       = 0x0020,
		compressed    = 0x0800,
		device        = 0x0040,
		directory     = 0x0010,
		encrypted     = 0x4000,
		hidden        = 0x0002,
		normal        = 0x0080,
		offline       = 0x1000,
		readonly      = 0x0001,
		reparse_point = 0x0400,
		system        = 0x0004,
		temporary     = 0x0100
	};

	using file_attributes = flag_enum<win::file_attribute>;

} // win