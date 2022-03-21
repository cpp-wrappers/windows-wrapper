#pragma once

#include "unexpected_handler.hpp"

#include <core/handle/declaration.hpp>
#include <core/exchange.hpp>

#include <handleapi.h>

namespace win {

	template<typename ObjectType, auto& CloseFunction>
	struct guarded_handle_base {
		::handle<ObjectType> m_handle;

		guarded_handle_base(::handle<ObjectType> handle) :
			m_handle{ handle }
		{}

		guarded_handle_base(guarded_handle_base&& other) {
			m_handle.value = exchange(other.hande, INVALID_HANDLE_VALUE);
		}

		::handle<ObjectType>& handle() { return m_handle; }
		const ::handle<ObjectType>& handle() const { return m_handle; }

		~guarded_handle_base() {
			if(m_handle.value != INVALID_HANDLE_VALUE) {
				if(!CloseFunction(handle())) {
					win::unexpected_handler();
				}
				m_handle.value = INVALID_HANDLE_VALUE;
			}
		}

		auto& value() const {
			return handle().value();
		}

		auto& value() {
			return handle().value();
		}

	};

} // win