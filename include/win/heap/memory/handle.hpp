#pragma once

namespace win {

	struct heap_memory;

} // win

#include <core/handle/declaration.hpp>
#include <core/integer.hpp>

template<>
struct handle<win::heap_memory> {
	uint8* m_data;

	auto& value() const {
		return m_data;
	}

	auto& value() {
		return m_data;
	}
};