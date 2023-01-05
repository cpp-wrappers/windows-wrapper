#pragma once

namespace win {

	enum class file_disposition {
		always_create = 2,
		create_new = 1,
		always_open = 4,
		open_existing = 3,
		truncate_existing = 5
	};

} // win