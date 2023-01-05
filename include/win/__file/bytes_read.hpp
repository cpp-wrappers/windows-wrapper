#pragma once

#include <integer.hpp>

namespace win {

	class bytes_read {
		uint32 value_;
	public:
		bytes_read(uint32 value) : value_{ value } {}
		operator uint32 () { return value_; }
	};

} // win