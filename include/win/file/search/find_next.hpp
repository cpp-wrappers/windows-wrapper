#pragma once

#include "handle.hpp"
#include "find_data.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<win::search>,
		types::are_contain_one_decayed<win::find_data>
	>::for_types<Args...>
	bool try_find_next_file(Args&&... args) {
		auto handle =
			elements::possibly_guarded_handle_of<win::search>(args...);

		auto& find_data =
			elements::decayed<win::find_data>(args...);

		return FindNextFileW(
			(HANDLE) handle.value,
			(LPWIN32_FIND_DATAW) &find_data
		);
	}

} // win