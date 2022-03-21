#pragma once

#include "../handle_base.hpp"

#include <core/handle/declaration.hpp>

namespace win {

	struct file;

} // win

template<>
struct handle<win::file> : win::handle_base {};