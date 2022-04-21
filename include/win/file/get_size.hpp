#pragma once

#include "handle.hpp"

#include <windows.h>

namespace win {

	uint64 inline get_file_size(handle<win::file> file) {
		uint32 high;

		uint32 low = GetFileSize(
			(HANDLE) file.value(),
			(LPDWORD) &high
		);

		return low | (uint64{ high } << 32);
	}

} // win

uint64 handle<win::file>::get_size() const {
	return win::get_file_size(*this);
}