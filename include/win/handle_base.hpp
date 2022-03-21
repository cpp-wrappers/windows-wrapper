#pragma once

#include <core/handle/declaration.hpp>

namespace win {

	struct handle_base {
		void* m_value;

		auto& value() const {
			return m_value;
		}

		auto& value() {
			return m_value;
		}
	};

} // win