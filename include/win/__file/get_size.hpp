#pragma once

#include "handle.hpp"

extern "C" __declspec (dllimport) uint32
GetFileSize(void* hFile, uint32* lpFileSizeHigh);

namespace win {

	uint64 inline get_file_size(handle<win::file> file) {
		uint32 high;

		uint32 low = GetFileSize(
			file.underlying(),
			&high
		);

		return low | (uint64{ high } << 32);
	}

} // win

uint64 handle_interface<win::file>::get_size() const {
	return win::get_file_size(
		handle<win::file>{underlying()}
	);
}