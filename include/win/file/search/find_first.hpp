#pragma once

#include "handle.hpp"
#include "find_data.hpp"
#include "../name.hpp"
#include "../../error.hpp"
#include "../../default_unexpected_handler.hpp"

#include <core/expected.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_decayed<win::file_name>,
		types::are_contain_one_decayed<win::find_data>
	>::for_types<Args...>
	expected<handle<win::search>, win::error>
	try_find_first_file(Args&&... args) {
		auto file_name =
			elements::decayed<win::file_name>(args...);
		
		auto& find_data =
			elements::decayed<win::find_data>(args...);

		auto result = FindFirstFileW(
			(LPCWSTR) file_name.begin(),
			(LPWIN32_FIND_DATAW) &find_data
		);

		if(result == INVALID_HANDLE_VALUE) {
			return win::get_last_error();
		}

		return handle<win::search>{ result };
	}

	template<typename... Args>
	handle<win::search> find_first_file(Args&&... args) {
		auto result = win::try_find_first_file(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::default_unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win