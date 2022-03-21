#pragma once

#include "handle.hpp"
#include "../error.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/expected.hpp>

namespace win {

	struct bytes_read : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<win::file>,
		types::are_contain_one_range_of<uint8>
	>::for_types<Args...>
	expected<win::bytes_read, win::error>
	try_read_file(Args&&... args) {
		auto& file = elements::possibly_guarded_handle_of<win::file>(args...);
		auto& buffer = elements::range_of<uint8>(args...);

		uint32 bytes_read;

		bool result = ReadFile(
			(HANDLE) file.value(),
			(LPVOID) buffer.data(),
			(DWORD) buffer.size(),
			(LPDWORD) &bytes_read,
			(LPOVERLAPPED) nullptr
		);

		if(!result) {
			return win::get_last_error();
		}

		return win::bytes_read{ bytes_read };
	}

} // win