#pragma once

__declspec(dllimport) extern "C" int CloseHandle(void* object_handle);

namespace win {

	inline bool try_close_handle(void* handle) {
		return CloseHandle(handle);
	}

} // win