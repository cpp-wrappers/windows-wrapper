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
	try_get_proc_address(c_string<char>);

	inline void* get_proc_address(c_string<char>);

};