#pragma once

__declspec(dllimport) void* GetProcAddress(void* module, const char* proc_name);

#include "./handle.hpp"
#include "../unexpected_handler.hpp"

inline expected<void*, win::error> handle_interface<win::library>::
try_get_proc_address(c_string<c_string_type::unknown_size> name) {
	void* result = GetProcAddress(this->underlying(), name.iterator());
	if(result == nullptr) {
		return win::get_last_error();
	}
	return result;
}

inline void* handle_interface<win::library>::
get_proc_address(c_string<c_string_type::unknown_size> name) {
	expected<void*, win::error> result = try_get_proc_address(name);
	if(result.is_unexpected()) {
		win::unexpected_handler(result.get_unexpected());
	}
	return result.get_expected();
}