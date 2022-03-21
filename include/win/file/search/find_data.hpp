#pragma once

#include "../attribute.hpp"
#include "../time.hpp"

#include <core/array.hpp>

#include <windows.h>

namespace win {

	extern "C" struct find_data {
		win::file_attributes attributes;
		win::file_time creation_time;
		win::file_time last_access_time;
		win::file_time last_write_time;
		uint32 file_size_hight; // TODO
		uint32 file_size_low;
		uint32 reserved_0;
		uint32 reserver_1;
		array<wchar_t, MAX_PATH> file_name;
		array<wchar_t, 14> alternate_file_name;
		uint32 file_type; // deprecated
		uint32 creator_type; // deprecated
		uint16 finder_flags; // deprecated
	};

} // win

static_assert(sizeof(win::find_data) > sizeof(WIN32_FIND_DATAW));

static_assert(
	__builtin_offsetof(win::find_data, attributes) ==
	__builtin_offsetof(WIN32_FIND_DATAW, dwFileAttributes)
);

static_assert(
	__builtin_offsetof(win::find_data, creation_time) ==
	__builtin_offsetof(WIN32_FIND_DATAW, ftCreationTime)
);

static_assert(
	__builtin_offsetof(win::find_data, file_name) ==
	__builtin_offsetof(WIN32_FIND_DATAW, cFileName)
);