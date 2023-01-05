#pragma once

#include <integer.hpp>

namespace win {

	struct security_attributes {
		uint32 nLength;
		void* security_descriptor_ptr;
		int inherit_handle;
	};

}