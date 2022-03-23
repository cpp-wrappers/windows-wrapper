#pragma once

#include "../handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/handle/possibly_guarded_of.hpp>

namespace win {

	enum class size_flag {
		no_serialize = 0x00000001
	};

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<win::heap>,
		types::are_may_contain_decayed<win::size_flag>,
		types::are_contain_one_decayed<handle<win::heap_memory>>
	>::for_types<Args...>
	nuint try_get_heap_memory_size(Args&&... args) {
		auto& heap = elements::possibly_guarded_handle_of<win::heap>(args...);
		
		win::size_flag flag{};

		if constexpr (
			types::are_contain_decayed<win::size_flag>::for_types<Args...>
		) { flag = elements::decayed<win::size_flag>(args...); }

		auto heap_mem = elements::decayed<handle<win::heap_memory>>(args...);

		return HeapSize(
			(HANDLE) heap.value(),
			(DWORD) flag,
			(LPCVOID) heap_mem.value()
		);
	}

	template<typename... Args>
	nuint get_heap_memory_size(Args&&... args) {
		nuint result = win::try_get_heap_memory_size(forward<Args>(args)...);
		if(result == (nuint) -1) {
			win::unexpected_handler();
		}
		return result;
	}

} // win