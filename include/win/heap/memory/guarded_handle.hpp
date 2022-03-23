#pragma once

#include "handle.hpp"
#include "../handle.hpp"

#include <core/handle/guarded_declaration.hpp>
#include <core/exchange.hpp>

#include <handleapi.h>

template<>
struct guarded_handle<win::heap_memory> {
	handle<win::heap> m_heap;
	handle<win::heap_memory> m_handle;

	auto& handle() const { return m_handle; }
	auto& handle() { return m_handle; }

	auto& value() const { return handle().value(); }
	auto& value() { return handle().value(); }

	auto& heap() const { return m_heap; }
	auto& heap() { return m_heap; }

	guarded_handle() = default;

	guarded_handle(
		::handle<win::heap> heap,
		::handle<win::heap_memory> handle
	) : 
		m_heap{ heap },
		m_handle{ handle }
	{}

	guarded_handle(guarded_handle&& other) :
		m_heap{ other.heap() },
		m_handle{ other.handle() }
	{
		other.handle().value() = nullptr;
	}

	guarded_handle& operator = (guarded_handle&& other) {
		m_heap = other.m_heap;
		m_handle.value() = exchange(other.value(), nullptr);
		return *this;
	}

	using value_type = uint8;

	const uint8* begin() const { return value(); }
	uint8* begin() { return value(); }

	const uint8* end() const { return begin() + size(); }
	uint8* end() { return begin() + size(); }

	inline nuint size() const;

	const uint8* data() const { return value(); }
	uint8* data() { return value(); }

	inline ~guarded_handle();
};

#include "free.hpp"

inline guarded_handle<win::heap_memory>::~guarded_handle() {
	if(m_handle.value() != nullptr) {
		heap().free(handle());
		m_handle.value() = nullptr;
	}
}

template<typename... Args>
guarded_handle<win::heap_memory>
handle<win::heap>::allocate_guarded(Args&&... args) const {
	return { *this, win::allocate_heap_memory(*this, forward<Args>(args)...) };
}

#include "size.hpp"

inline nuint guarded_handle<win::heap_memory>::size() const {
	return win::get_heap_memory_size(heap(), handle());
}