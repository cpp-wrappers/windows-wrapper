#pragma once

#include <integer.hpp>

namespace win {

	struct overlapped {
		unsigned long* internal;
		unsigned long* internal_high;
		union {
			struct {
				uint32 offset;
				uint32 offset_high;
			};
			void* pointer;
		};
		void* h_event;
	};

}