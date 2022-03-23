#pragma once

#include "handle.hpp"
#include "access.hpp"
#include "share.hpp"
#include "disposition.hpp"
#include "attribute.hpp"
#include "name.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <core/wc_string.hpp>
#include <core/expected.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

#include <fileapi.h>
#include <handleapi.h>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<win::file_name>,
		types::are_contain_one_decayed<win::file_accesses>,
		types::are_may_contain_one_decayed<win::file_shares>,
		types::are_contain_one_decayed<win::file_disposition>,
		types::are_may_contain_one_decayed<win::file_attributes>
	>::for_types<Args...>
	expected<handle<win::file>, win::error>
	try_create_file(Args&&... args) {
		wc_string name =
			elements::decayed<win::file_name>(args...);

		win::file_accesses access =
			elements::decayed<win::file_accesses>(args...);

		win::file_shares shares{};

		if constexpr (
			types::are_contain_decayed<win::file_shares>::for_types<Args...>
		) {
			shares = elements::decayed<win::file_shares>(args...);
		}

		win::file_disposition disposition =
			elements::decayed<win::file_disposition>(args...);

		win::file_attributes attributes{};

		if constexpr (
			types::are_contain_decayed<win::file_attributes>::for_types<Args...>
		) {
			attributes = elements::decayed<win::file_attributes>(args...);
		}

		HANDLE result = CreateFileW(
			(LPCWSTR) name.begin(),
			(DWORD) access.value,
			(DWORD) shares.value,
			(LPSECURITY_ATTRIBUTES) nullptr,
			(DWORD) disposition,
			(DWORD) attributes.value,
			(HANDLE) nullptr
		);

		if(result == INVALID_HANDLE_VALUE) {
			return win::get_last_error();
		}

		return handle<win::file>{ result };
	}

	template<typename... Args>
	handle<win::file> create_file(Args&&... args) {
		auto result = win::try_create_file(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win