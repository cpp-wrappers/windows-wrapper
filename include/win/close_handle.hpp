#pragma once

#include "handle_base.hpp"

#include <handleapi.h>

namespace win {

	inline bool try_close_handle(handle_base& handle) {
		return CloseHandle((HANDLE) handle.value());
	}

} // win