# ifndef SK_CONFIG_HPP_
# define SK_CONFIG_HPP_

# include <exception>

namespace sk {
namespace config {

extern constexpr const char* version_string();

enum class BuildOptionsEnum {
    pedantic_exceptions,
    debug_output,
    profiling,
    physics_debug,
};

template<BuildOptionsEnum option>
bool is_enabled();

} // config

void throw_pedantic(const std::exception& ex);

} // sk

# endif // SK_CONFIG_HPP_
