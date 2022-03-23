#pragma once

#include "handle.hpp"
#include "bytes_written.hpp"
#include "../error.hpp"

#include <core/expected.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/range/basic.hpp>
#include <core/handle/possibly_guarded_of.hpp>

namespace win {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<win::file>,
		types::are_contain_basic_range
	>::for_types<Args...>
	expected<win::bytes_written, win::error>
	try_write_file(Args&&... args) {
		auto& handle = elements::possibly_guarded_handle_of<win::file>(args...);
		auto& buffer = elements::basic_range(args...);

		win::bytes_written written;

		if(!WriteFile(
			(HANDLE) handle.value(),
			(LPCVOID) buffer.data(),
			(DWORD) buffer.size() * sizeof(range::value_type<decltype(buffer)>),
			(LPDWORD) &written,
			(LPOVERLAPPED) nullptr
		)) {
			return win::get_last_error();
		}
		
		return written;
	}

	template<typename... Args>
	win::bytes_written write_file(Args&&... args) {
		auto result = win::try_write_file(forward<Args>(args)...);
		if(result.is_unexpected()) {
			win::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // win

template<typename... Args>
win::bytes_written handle<win::file>::write(Args&&... args) const {
	return win::write_file(*this, forward<Args>(args)...);
}