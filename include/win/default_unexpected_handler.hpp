#pragma once

#include "error.hpp"

#include <core/expected.hpp>

namespace win {

	[[ noreturn ]]
	inline void default_unexpected_handler() {
		abort();
		__builtin_unreachable();
	}

	[[ noreturn ]]
	inline void default_unexpected_handler([[maybe_unused]] win::error error) {
		win::default_unexpected_handler();
	}

} // win