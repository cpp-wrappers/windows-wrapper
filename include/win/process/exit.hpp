#pragma once

#include <core/integer.hpp>

#include <processthreadsapi.h>

namespace win {

	[[ noreturn ]]
	inline void exit_process(uint32 code) {
		ExitProcess(code);
	}

} // win