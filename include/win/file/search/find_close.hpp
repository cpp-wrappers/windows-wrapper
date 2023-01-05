#pragma once

#include "handle.hpp"

namespace win {

	inline bool try_find_close(handle<win::search> search) {
		return FindClose((HANDLE) search.value());
	}

} // win