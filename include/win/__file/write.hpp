#pragma once

#include "./handle.hpp"
#include "./bytes_written.hpp"
#include "./overlapped.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"

#include <types.hpp>
#include <type.hpp>
#include <tuple.hpp>
#include <expected.hpp>
#include <range.hpp>

extern "C" __declspec (dllimport) int
WriteFile(
	void* file_handle,
	const void* buffer,
	uint32 number_of_bytes_to_write,
	win::bytes_written* number_of_bytes_written_ptr,
	win::overlapped* overlapped_ptr
);

namespace win {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		contain_one_satisfying_predicate<
			is_same_as<handle<win::file>>.while_decayed
		>,
		contain_one_satisfying_predicate<is_basic_range>
	>
	expected<win::bytes_written, win::error>
	try_write_file(Args&&... args) {
		handle<win::file> file =
			tuple{ args... }.template get_satisfying_predicate<
				is_same_as<handle<win::file>>.while_decayed
			>();

		auto& buffer = tuple{ args... }.template get_satisfying_predicate<
			is_basic_range
		>();

		win::bytes_written written;

		if(!WriteFile(
			file.underlying(),
			buffer.iterator(),
			buffer.size() * sizeof(
				remove_reference<range_element_type<decltype(buffer)>>
			),
			&written,
			nullptr
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
win::bytes_written
handle_interface<win::file>::write_from(Args&&... args) const {
	return win::write_file(
		handle<win::file>{ this->underlying() },
		forward<Args>(args)...
	);
}