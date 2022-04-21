#pragma once

#include "../../handle_base.hpp"

#include <core/handle.hpp>

namespace win {

	struct search;

} // win

template<>
struct handle<win::search> : win::handle_base {};