#ifndef SK_READ_OPTIONS_HPP_
#define SK_READ_OPTIONS_HPP_

#include <filesystem>
#include <optional>

namespace sk {

struct ConfigureOptions {
    std::filesystem::path data_path;
    std::filesystem::path settings_path;
    std::filesystem::path saves_path;
};

std::optional<ConfigureOptions> read_options(int argc, const char* argv[]) noexcept;
} // namespace sk

#endif // SK_READ_OPTIONS_HPP_
