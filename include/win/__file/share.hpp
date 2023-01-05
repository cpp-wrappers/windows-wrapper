#pragma once

#include <enum_flags.hpp>

namespace win {

	enum class file_share {
		deletion = 0x00000004,
		read     = 0x00000001,
		write    = 0x00000002
	};

	using file_shares = enum_flags<file_share>;

} // win