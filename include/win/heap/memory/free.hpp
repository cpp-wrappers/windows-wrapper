#pragma once

#include "handle.hpp"
#include "../handle.hpp"
#include "../../unexpected_handler.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace win {

	enum class free_flag {
		no_serialize = 0x00000001
	};

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<win::heap>>,
		types::are_may_contain_one_decayed<win::free_flag>,
		types::are_contain_one_decayed<handle<win::heap_memory>>
	>::for_types<Args...>
	bool try_free_heap_memory(Args&&... args) {
		auto heap_memory = elements::decayed<handle<win::heap>>(args...);

		win::free_flag flag{};

		if constexpr (
			types::are_contain_decayed<win::free_flag>::for_types<Args...>
		) { flag = elements::decayed<win::free_flag>(args...); }

		auto mem = elements::decayed<::handle<win::heap_memory>>(args...);

		return HeapFree(
			(HANDLE) heap_memory,
			(DWORD) flag,
			(LPVOID) mem.value()
		);
	}

	template<typename... Args>
	void free_heap_memory(Args&&... args) {
		if(!win::try_free_heap_memory(forward<Args>(args)...)) {
			win::unexpected_handler(win::get_last_error());
		}
	}

} // win

template<typename... Args>
void handle<win::heap>::free(Args&&... args) const {
	return win::free_heap_memory(*this, forward<Args>(args)...);
}