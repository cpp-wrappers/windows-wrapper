#pragma once

#include "bytes_read.hpp"
#include "bytes_written.hpp"
#include "../handle_base.hpp"

#include <core/integer.hpp>
#include <core/handle.hpp>

namespace win {

	struct file;

} // win

template<>
struct handle<win::file> : win::handle_base {

	inline uint64 get_size() const;

	template<typename... Args>
	win::bytes_read read(Args&&...) const;

	template<typename... Args>
	win::bytes_written write(Args&&...) const;

};

#include "get_size.hpp"
#include "read.hpp"
#include "write.hpp"