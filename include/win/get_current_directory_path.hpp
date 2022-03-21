#pragma once

#include <core/span.hpp>
#include <core/range/of_value_type_same_as.hpp>

#include <windows.h>

namespace win {

	inline nuint get_current_directory_path_length() {
		return GetCurrentDirectory(0, nullptr);
	}

	template<range::of<wchar_t> Range>
	inline nuint get_current_directory_path(Range& range) {
		return GetCurrentDirectory(range.size(), range.data());
	}

	template<typename F>
	void view_current_working_directory(F&& f) {
		auto len = get_current_directory_path_length();
		wchar_t storage[len];
		span s{ storage, len };
		win::get_current_directory_path(s);
		f(s);
	}

} // win