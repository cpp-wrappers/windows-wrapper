#pragma once

#include "handle.hpp"

#include <core/handle/possibly_guarded_of.hpp>

#include <windows.h>

namespace win {

	uint64 get_file_size(possibly_guarded_handle_of<win::file> auto&& file) {
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