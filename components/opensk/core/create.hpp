#ifndef SK_CORE_CREATE_HPP
#define SK_CORE_CREATE_HPP

#include <optional>
#include <spdlog/spdlog.h>

namespace sk {

template<class T, class... Args>
void create(std::optional<T>& t, Args&&... args) {
    try {
        t.emplace(std::forward<Args>(args)...);
    } catch (std::exception const& ex) {
        spdlog::error(ex.what());
    }
}

template<class T, class... Args>
std::optional<T> create(Args&&... args) {
    std::optional<T> t{};
    sk::create(t, std::forward<Args>(args)...);
    return t;
}
}// namespace sk

#endif// SK_CORE_CREATE_HPP
