#include <config.hpp>
#include <config_def.hpp>

namespace sk {
namespace config {

constexpr const char* version_string() {
    return SK_VERSION_STRING;
}

template<>
bool is_enabled<BuildOptionsEnum::pedantic_exceptions>() {
    return SK_PEDANTIC_EXCEPTIONS;
}

template<>
bool is_enabled<BuildOptionsEnum::debug_output>() {
    return SK_DEBUG_OUTPUT;
}

template<>
bool is_enabled<BuildOptionsEnum::profiling>() {
    return SK_PROFILING;
}

template<>
bool is_enabled<BuildOptionsEnum::physics_debug>() {
    return SK_PHYSICS_DEBUG;
}

}// namespace config

void throw_pedantic(std::exception const& ex) {
    if (sk::config::is_enabled<sk::config::BuildOptionsEnum::pedantic_exceptions>()) {
        throw ex;
    }
}

}// namespace sk