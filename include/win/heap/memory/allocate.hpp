#pragma once

#include "handle.hpp"
#include "../handle.hpp"
#include "../../unexpected_handler.hpp"

#include <core/expected.hpp>
#include <core/handle/possibly_guarded_of.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/flag_enum.hpp>

#include <heapapi.h>

namespace win {

	enum class allocation_flag {
		enable_execute      = 0x00040000,
		generate_exceptions = 0x00000004,
		no_serialize        = 0x00000001
	};
	
	using allocation_flags = flag_enum<win::allocation_flag>;

	struct bytes : wrapper::of_integer<nuint> {};

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<win::heap>,
		types::are_may_contain_one_decayed<win::allocation_flags>,
		types::are_contain_one_decayed<win::bytes>
	>::for_types<Args...>
	handle<win::heap_memory>
	try_allocate_heap_memory(Args&&... args) {
		auto& handle = elements::possibly_guarded_handle_of<win::heap>(args...);

		win::allocation_flags flags{};

		if constexpr (
			types::are_contain_decayed<win::allocation_flags>::for_types<Args...>
		) { flags = elements::decayed<win::allocation_flags>(args...); }

		auto bytes = elements::decayed<win::bytes>(args...);

		return {
			(uint8*) HeapAlloc(
				(HANDLE) handle.value(),
				(DWORD) flags.value,
				(SIZE_T) bytes
			)
		};
	}

	template<typename... Args>
	handle<win::heap_memory> allocate_heap_memory(Args&&... args) {
		auto result = win::try_allocate_heap_memory(forward<Args>(args)...);
		if(result.value() == nullptr) {
			win::unexpected_handler();
		}
		return result;
	}

} // win

template<typename... Args>
handle<win::heap_memory>
handle<win::heap>::allocate(Args&&... args) const {
	return win::allocate_heap_memory(*this, forward<Args>(args)...);
}