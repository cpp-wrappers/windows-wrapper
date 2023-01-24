#pragma once

__declspec(dllimport) extern "C" void* GetProcAddress(
	void* module, const char* proc_name
);

#include "./handle.hpp"
#include "../unhandled.hpp"

#include <c_string.hpp>

inline expected<void*, win::error> handle_interface<win::library>::
try_get_proc_address(any_c_string auto name) {
	void* result = GetProcAddress(this->underlying(), name.iterator());
	if(result == nullptr) {
		return win::get_last_error();
	}
	return result;
}

inline void* handle_interface<win::library>::
get_proc_address(any_c_string auto name) {
	expected<void*, win::error> result = try_get_proc_address(name);
	if(result.is_unexpected()) {
		win::unhandled(result.get_unexpected());
	}
	return result.get_expected();
}