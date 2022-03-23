#pragma once

#include "../unexpected_handler.hpp"
#include "../heap/handle.hpp"

#include <core/expected.hpp>

#include <heapapi.h>

namespace win {

	inline expected<handle<win::heap>, win::error>
	try_get_process_heap() {
		auto result = GetProcessHeap();
		if(result == nullptr) {
			return win::get_last_error();
		}
		return { handle<win::heap>{ result } };
	}

	inline handle<win::heap> get_process_heap() {
		auto result = win::try_get_process_heap();
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win