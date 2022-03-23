#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../guarded_handle_base.hpp"

#include <core/handle/guarded_declaration.hpp>

template<>
struct guarded_handle<win::heap> :
	win::guarded_handle_base<win::heap, win::try_destroy_heap>
{
	using base_type =win::guarded_handle_base<win::heap, win::try_destroy_heap>;

	using base_type::base_type;

	template<typename... Args>
	::handle<win::heap_memory> allocate(Args&&... args) const {
		return handle().allocate(forward<Args>(args)...);
	}

	template<typename... Args>
	guarded_handle<win::heap_memory> allocate_guarded(Args&&... args) const {
		return handle().allocate_guarded(forward<Args>(args)...);
	}

	template<typename... Args>
	void free(Args&&... args) const {
		handle().free(forward<Args>(args)...);
	}

};