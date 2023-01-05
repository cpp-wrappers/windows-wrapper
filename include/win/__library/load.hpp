#pragma once

#include "./handle.hpp"
#include "../__file/name.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <body.hpp>
#include <c_string.hpp>
#include <expected.hpp>

__declspec(dllimport) extern "C" void* LoadLibraryW(
	const wchar_t* lib_file_name_ptr
);

namespace win {

	inline expected<body<win::library>, win::error> try_load_library(
		win::file_name file_name
	) {
		void* result = LoadLibraryW(file_name.iterator());
		if(result == nullptr) {
			return win::get_last_error();
		}
		return body<win::library>{ result };
	}

	inline body<win::library> load_library(win::file_name file_name) {
		expected<body<win::library>, win::error> result
			= win::try_load_library(file_name);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return move(result.get_expected());
	}

}