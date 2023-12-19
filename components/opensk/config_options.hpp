#ifndef SK_CONFIG_OPTIONS_HPP
#define SK_CONFIG_OPTIONS_HPP

#ifdef SK_ENABLE_DEBUG_OUTPUT
#define SK_OPTION_DEBUG_OUTPUT true
#else
#define SK_OPTION_DEBUG_OUTPUT false
#endif

#ifdef SK_ENABLE_PEDANTIC_EXCEPTIONS
#define SK_OPTION_PEDANTIC_EXCEPTIONS true
#else
#define SK_OPTION_PEDANTIC_EXCEPTIONS false
#endif

#ifdef SK_ENABLE_PHYSICS_DEBUG
#define SK_OPTION_PHYSICS_DEBUG true
#else
#define SK_OPTION_PHYSICS_DEBUG false
#endif

#ifdef SK_ENABLE_PROFILING
#define SK_OPTION_PROFILING true
#else
#define SK_OPTION_PROFILING false
#endif

namespace sk::config {

enum class BuildOptionsEnum {
    debug_output,
    pedantic_exceptions,
    physics_debug,
    profiling,
};

template<BuildOptionsEnum>
inline constexpr bool is_enabled = false;

template<>
inline constexpr bool is_enabled<BuildOptionsEnum::debug_output> = SK_OPTION_DEBUG_OUTPUT;

template<>
inline constexpr bool is_enabled<BuildOptionsEnum::pedantic_exceptions> = SK_OPTION_PEDANTIC_EXCEPTIONS;

template<>
inline constexpr bool is_enabled<BuildOptionsEnum::physics_debug> = SK_OPTION_PHYSICS_DEBUG;

template<>
inline constexpr bool is_enabled<BuildOptionsEnum::profiling> = SK_OPTION_PROFILING;
}// namespace sk::config

#endif// SK_CONFIG_OPTIONS_HPP
