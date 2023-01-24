#pragma once

#include "error.hpp"

#include <optional.hpp>

namespace win {

	struct unhandled_t {
		[[noreturn]] void operator () () const;
		[[noreturn]] void operator () (win::error error) const;
	};

	static constexpr unhandled_t unhandled{};

} // win