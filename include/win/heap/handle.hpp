#pragma once

namespace win {

	struct heap;
	struct heap_memory;

} // win

#include "../handle_base.hpp"

#include <core/handle/declaration.hpp>
#include <core/handle/guarded_declaration.hpp>

template<>
struct handle<win::heap> : win::handle_base {

	template<typename... Args>
	handle<win::heap_memory> allocate(Args&&... args) const;

	template<typename... Args>
	guarded_handle<win::heap_memory> allocate_guarded(Args&&... args) const;

	template<typename... Args>
	void free(Args&&... args) const;

};

#include "./memory/allocate.hpp"
#include "./memory/guarded_handle.hpp"
#include "./memory/free.hpp"