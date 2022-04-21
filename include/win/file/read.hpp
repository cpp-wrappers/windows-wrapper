#pragma once

#include "handle.hpp"
#include "bytes_read.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/range/basic.hpp>
#include <core/range/value_type.hpp>
#include <core/expected.hpp>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<win::file>>,
		types::are_contain_basic_range
	>::for_types<Args...>
	expected<win::bytes_read, win::error>
	try_read_file(Args&&... args) {
		auto file = elements::decayed<handle<win::file>>(args...);
		auto& buffer = elements::basic_range(args...);

		uint32 bytes_read;

		if(!ReadFile(
			(HANDLE) file.value(),
			(LPVOID) buffer.data(),
			(DWORD) buffer.size() * sizeof(range::value_type<decltype(buffer)>),
			(LPDWORD) &bytes_read,
			(LPOVERLAPPED) nullptr
		)) {
			return win::get_last_error();
		}

		return win::bytes_read{ bytes_read };
	}

	template<typename... Args>
	win::bytes_read read_file(Args&&... args) {
		auto result = win::try_read_file(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win

template<typename... Args>
win::bytes_read handle<win::file>::read(Args&&... args) const {
	return win::read_file(*this, forward<Args>(args)...);
}