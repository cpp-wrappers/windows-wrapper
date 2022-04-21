#pragma once

#include <core/integer.hpp>

#include <windows.h>

namespace win {

	[[ noreturn ]]
	inline void exit_process(uint32 code) {
		ExitProcess(code);
	}

	inline void fatal_exit(uint32 code) {
		FatalExit(code);
	} 

} // win