#pragma once

#include "handle.hpp"
#include "find_data.hpp"
#include "../../unexpected_handler.hpp"

#include <core/expected.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<win::search>>,
		types::are_contain_one_decayed<win::find_data>
	>::for_types<Args...>
	win::error
	try_find_next_file(Args&&... args) {
		auto handle = elements::decayed<::handle<win::search>>(args...);

		auto& find_data = elements::decayed<win::find_data>(args...);

		auto result = FindNextFileW(
			(HANDLE) handle.value(),
			(LPWIN32_FIND_DATAW) &find_data
		);

		if(result == 0) {
			return win::get_last_error();
		}

		return win::error::success;
	}

	template<typename... Args>
	bool find_next_file(Args&&... args) {
		auto result = win::try_find_next_file(forward<Args>(args)...);
		if(result != error::success) {
			if(result != error::no_more_files) {
				win::unexpected_handler(win::get_last_error());
			}
			return false;
		}
		return true;
	}

} // win