#pragma once

#include "./handle.hpp"
#include "./access.hpp"
#include "./share.hpp"
#include "./disposition.hpp"
#include "./attribute.hpp"
#include "./name.hpp"
#include "./security_attributes.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <types.hpp>
#include <tuple.hpp>
#include <expected.hpp>

__declspec (dllimport) extern "C" void* CreateFileW(
	const wchar_t* file_name_ptr,
	uint32 desired_access,
	uint32 share_mode,
	win::security_attributes* security_attributes_ptr,
	uint32 creation_disposition,
	uint32 flags_and_attributes,
	void* template_file_handle
);

namespace win {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<win::file_name> == 1,
		count_of_decayed_same_as<win::file_accesses> == 1,
		count_of_decayed_same_as<win::file_disposition> == 1,
		count_of_decayed_same_as<win::file_shares> <= 1,
		count_of_decayed_same_as<win::file_attributes> <= 1
	>
	expected<body<win::file>, win::error>
	try_create_file(Args&&... args) {
		win::file_name name = tuple{ args... }.template
			get_decayed_same_as<win::file_name>();

		win::file_accesses access = tuple{ args... }.template
			get_decayed_same_as<win::file_accesses>();

		win::file_disposition disposition = tuple{ args... }.template
			get_decayed_same_as<win::file_disposition>();

		win::file_shares shares{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<win::file_shares> > 0
		) {
			shares = tuple{ args... }.template
				get_decayed_same_as<win::file_shares>();
		}

		win::file_attributes attributes{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<win::file_attributes> > 0
		) {
			shares = tuple{ args... }.template
				get_decayed_same_as<win::file_attributes>();
		}

		handle<win::file> handle = CreateFileW(
			name.iterator(),
			(uint32) access,
			(uint32) shares,
			(win::security_attributes*) nullptr,
			(uint32) disposition,
			(uint32) attributes,
			nullptr
		);

		if(handle.is_invalid()) {
			return win::get_last_error();
		}

		return body<win::file>{ handle.underlying() };
	}

	template<typename... Args>
	body<win::file> create_file(Args&&... args) {
		auto result = win::try_create_file(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return move(result.get_expected());
	}

} // win