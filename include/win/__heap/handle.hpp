#pragma once

namespace win {

	struct heap;
	struct heap_memory;

} // win

#include <handle.hpp>

template<>
struct handle_underlying_t<win::heap> {
	using type = void*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<win::heap> : handle_interface_base<win::heap> {

	template<typename... Args>
	handle<win::heap_memory> allocate(Args&&... args) const;

	template<typename... Args>
	void free(Args&&... args) const;

};