#pragma once

#include "./handle.hpp"

#include <body.hpp>

__declspec (dllimport) extern "C" int FreeLibrary(void* library);

template<>
inline void body<win::library>::do_destroy() {
	::FreeLibrary(this->soul_handle_.underlying());
}