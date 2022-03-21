#pragma once

#ifndef WIN_UNEXPECTED_HANDLER_HEADER

#include "error.hpp"

namespace win {

	[[ noreturn ]]
	inline void unexpected_handler() {
		abort();
	}

	[[ noreturn ]]
	inline void unexpected_handler([[maybe_unused]] win::error error);

} // win

#else

#include_next WIN_UNEXPECTED_HANDLER_HEADER

#endif