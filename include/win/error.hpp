#pragma once

#include "errhandlingapi.h"

namespace win {

	enum class error {
		success = 0x00000000,
		invalid_function = 0x00000001,
		file_not_found = 0x00000002,
		path_not_found = 0x00000003,
		too_many_open_files = 0x00000004,
		access_denied = 0x00000005,
		invalid_handle = 0x00000006
	};

	inline win::error get_last_error() {
		return (win::error) GetLastError();
	}

} // win