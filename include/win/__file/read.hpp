#pragma once

#include "./handle.hpp"
#include "./bytes_read.hpp"
#include "./overlapped.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <types.hpp>
#include <expected.hpp>
#include <tuple.hpp>
#include <range.hpp>

extern "C" __declspec (dllimport) int
ReadFile(
	void* file_handle, void* buffer, uint32 number_of_bytes_to_read,
	uint32* number_of_bytes_read_ptr, win::overlapped* overlapped_ptr
);

namespace win {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<win::file>> == 1,
		count_of_satisfying_predicate<is_basic_range> == 1
	>
	expected<win::bytes_read, win::error>
	try_read_file(Args&&... args) {
		handle<win::file> file = tuple{ args... }.template
			get_decayed_same_as<handle<win::file>>();

		auto& buffer = tuple{ args... }.template
			get_satisfying_predicate<is_basic_range>();

		uint32 bytes_read;

		if(!ReadFile(
			file.underlying(),
			buffer.iterator(),
			buffer.size() * sizeof(
				remove_reference<range_element_type<decltype(buffer)>>
			),
			&bytes_read,
			nullptr
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
win::bytes_read handle_interface<win::file>::read_to(Args&&... args) const {
	return win::read_file(
		handle<win::file>{ this->underlying() },
		forward<Args>(args)...
	);
}