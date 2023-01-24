#include <win/file.hpp>
#include <win/process/exit.hpp>

#include <array.hpp>

extern "C" int wWinMain(
	void*, void*, wchar_t* arg, int
) {
	handle<win::file> file = win::create_file(
		win::file_name{ arg },
		win::file_accesses{ win::file_access::read },
		win::file_disposition::open_existing
	);

	array<char, 1024> buff;

	win::bytes_read read = 0;
	while((read = file->read_to(buff)) > 0) {
		win::get_std_out().write_from(buff.shrink_view(read));
	}
}

namespace win {

	[[ noreturn ]] void unhandled_t::operator () () const {
		win::exit(-1);
	}

	[[ noreturn ]] void unhandled_t::operator () (win::error error) const {
		win::exit((int32) error);
	}

}