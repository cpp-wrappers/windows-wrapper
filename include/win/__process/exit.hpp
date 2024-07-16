#pragma once

#include <integer.hpp>

__declspec(dllimport) extern "C" __declspec(noreturn)
void ExitProcess(unsigned exit_code);

__declspec(dllimport) extern "C"
void FatalExit(int exit_code);

namespace win {

	[[ noreturn ]]
	inline void exit(uint32 code) {
		ExitProcess(code);
	}

	inline void fatal_exit(uint32 code) {
		FatalExit(code);
	}

} // win