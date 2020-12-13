#pragma once

#include "handle.hpp"
#include <memory>
#include <iterator>
#include <utility>
#include <cxx_util/flags.hpp>

namespace windows {

namespace internal {
    struct find_data {
        std::wstring file_name;
        int file_attribs;
        int file_type;
    };

    void* find_first_file(const wchar_t* file_name, find_data& fd);
    bool find_next_file(void* handle, find_data& fd);
    bool find_close(void* h);
}

struct search_handle : public handle {
    using handle::handle;

    search_handle(void* h):handle(h){}

    ~search_handle() noexcept(false) {
        if(raw != internal::invalid_handle && !internal::find_close(std::exchange(raw, internal::invalid_handle)))
            throw error{"cannot close search handle"};
    }
};

struct file_search_iterator {
    using value_type = std::wstring;
    using iterator_category = std::input_iterator_tag;

    internal::find_data fd{};
    std::shared_ptr<search_handle> sh;

    file_search_iterator() {}

    file_search_iterator(std::wstring file_name) noexcept(false) {
        auto h = internal::find_first_file(file_name.c_str(), fd);

        if(h == internal::invalid_handle)
            throw error{"cannot find first file"};

        sh = std::make_shared<search_handle>(h);
    }

    file_search_iterator(const file_search_iterator& fsi) = default;
    file_search_iterator& operator = (const file_search_iterator& fsi) = default;

    std::wstring operator * () const {
        return {fd.file_name};
    }

    auto& operator ++ () {
        if(sh && internal::raw(*sh) != internal::invalid_handle && !internal::find_next_file(internal::raw(*sh), fd)) {
            sh.reset();
        }
        return *this;
    }

    bool operator == (const file_search_iterator other) { return !other.sh && !sh; }
};

inline void swap(file_search_iterator& fsi0, file_search_iterator& fsi1) {
    swap(fsi0.sh, fsi1.sh);
}

inline const file_search_iterator& begin(const file_search_iterator& iter) { return iter; }
inline file_search_iterator end(const file_search_iterator& iter) { return {}; }

}