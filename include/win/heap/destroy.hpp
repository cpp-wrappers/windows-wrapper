#pragma once

#include "handle.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

namespace win {

	inline bool try_destroy_heap(handle<win::heap> handle) {
		return HeapDestroy((HANDLE) handle.value());
	}

	inline void destroy_heap(handle<win::heap> handle) {
		if(!try_destroy_heap(handle)) {
			win::unexpected_handler(win::get_last_error());
		}
	}

} // win