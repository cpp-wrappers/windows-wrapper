#pragma once

#include "handle.hpp"
#include "../guarded_handle_base.hpp"
#include "../close_handle.hpp"

#include <core/handle/guarded_declaration.hpp>

namespace win {

} // win

template<>
struct guarded_handle<win::file> :
	win::guarded_handle_base<win::file, win::try_close_handle
> {

};