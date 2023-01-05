#pragma once

#include "./handle.hpp"

__declspec (dllimport) extern "C" void* GetStdHandle(uint32 handle);

namespace win {

	enum class std_handle {
		input = -10,
		output = -11,
		error = -12
	};

	inline handle<win::file> get_std_handle(win::std_handle type) {
		return { GetStdHandle((uint32) type) };
	}

	inline handle<win::file> get_std_in() {
		return get_std_handle(std_handle::input);
	}

	inline handle<win::file> get_std_out() {
		return get_std_handle(std_handle::output);
	}

	inline handle<win::file> get_std_err() {
		return get_std_handle(std_handle::error);
	}

} // win