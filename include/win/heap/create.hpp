#pragma once

#include "handle.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <core/expected.hpp>
#include <core/flag_enum.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include <heapapi.h>

namespace win {

	struct initial_size { nuint _; operator nuint () const { return _; } };
	struct maximum_size { nuint _; operator nuint () const { return _; } };

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_may_contain_one_decayed<win::allocation_flags>,
		types::are_may_contain_one_decayed<win::initial_size>,
		types::are_may_contain_one_decayed<win::maximum_size>
	>::for_types<Args...>
	expected<handle<win::heap>, win::error>
	try_create_heap(Args&&... args) {
		win::allocation_flags flags{};

		if constexpr(
			types::are_contain_decayed<
				win::allocation_flags
			>::for_types<Args...>
		) { flags = elements::decayed<win::allocation_flags>(args...); }

		win::initial_size initial{};

		if constexpr(
			types::are_contain_decayed<win::initial_size>::for_types<Args...>
		) { initial = elements::decayed<win::initial_size>(args...); }

		win::maximum_size maximum{};

		if constexpr(
			types::are_contain_decayed<win::maximum_size>::for_types<Args...>
		) { maximum = elements::decayed<win::maximum_size>(args...); }

		HANDLE result = HeapCreate(
			(DWORD) flags.value,
			(SIZE_T) initial,
			(SIZE_T) maximum
		);

		if(result == nullptr) {
			return win::get_last_error();
		}

		return handle<win::heap>{ result };
	}

	template<typename... Args>
	handle<win::heap> create_heap(Args&&... args) {
		auto result = win::try_create_heap(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win