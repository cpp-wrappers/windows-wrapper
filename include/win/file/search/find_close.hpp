#pragma once

#include "handle.hpp"

#include <fileapi.h>

namespace win {

	inline bool try_find_close(handle<win::search> search) {
		return FindClose((HANDLE) search.value);
	}

} // win