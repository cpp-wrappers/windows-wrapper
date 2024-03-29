#pragma once

#include "../error.hpp"

#include <handle.hpp>
#include <c_string.hpp>
#include <expected.hpp>

namespace win {

	struct library;

}

template<>
struct handle_underlying_t<win::library> {
	using type = void*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<win::library> : handle_interface_base<win::library> {

	inline expected<void*, win::error>
	try_get_proc_address(any_c_string auto);

	inline void* get_proc_address(any_c_string auto);

};