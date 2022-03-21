#pragma once

#include <core/wrapper/of_integer.hpp>

namespace win {

	struct file_time {
		uint32 low_date_time;
		uint32 high_date_time;
	};

} // win