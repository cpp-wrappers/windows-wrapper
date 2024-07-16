#pragma once

#include "../unhandled.hpp"
#include "../__heap/handle.hpp"

#include <expected.hpp>

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
			win::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win