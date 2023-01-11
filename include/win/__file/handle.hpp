#pragma once

#include "./bytes_read.hpp"
#include "./bytes_written.hpp"

#include "../__handle/close.hpp"

#include <handle.hpp>

namespace win {

	struct file;

} // win

template<>
struct handle_underlying_t<win::file> {
	using type = void*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<win::file> : handle_interface_base<win::file> {

	inline uint64 get_size() const;

	template<typename... Args>
	win::bytes_read read_to(Args&&...) const;

	template<typename... Args>
	win::bytes_written write_from(Args&&...) const;

};

#include <body.hpp>
#include "../unexpected_handler.hpp"

template<>
inline void body<win::file>::do_destroy() {
	bool result = win::try_close_handle(this->soul_handle_.underlying());
	if(!result) {
		win::error err = win::get_last_error();
		win::unexpected_handler(err);
	}
}