#pragma once

#include "file/handle.hpp"

#include <processenv.h>

namespace win {

	enum class std_handle {
		input = -10,
		output = -11,
		error = -12
	};

	inline handle<win::file> get_std_handle(win::std_handle type) {
		return { GetStdHandle((DWORD) type) };
	}

} // win