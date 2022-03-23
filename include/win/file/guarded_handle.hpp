#pragma once

#include "handle.hpp"
#include "../guarded_handle_base.hpp"
#include "../close_handle.hpp"

#include <core/handle/guarded_declaration.hpp>

namespace win {

} // win

template<>
struct guarded_handle<win::file> :
	win::guarded_handle_base<win::file, win::try_close_handle>
{
	using base_type =
		win::guarded_handle_base<win::file, win::try_close_handle>;

	using base_type::base_type;

	uint64 get_size() const { return handle().get_size(); }

	template<typename... Args>
	win::bytes_read read(Args&&... args) const {
		return handle().read(forward<Args>(args)...);
	}

};