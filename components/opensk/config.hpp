#ifndef SK_CONFIG_HPP
#define SK_CONFIG_HPP

#include <config_options.hpp>
#include <exception>

// #include <boost/preprocessor/control/if.hpp>
// #include <boost/preprocessor/facilities/empty.hpp>
// #include <boost/preprocessor/logical/bool.hpp>

#include <boost/predef/compiler/clang.h>

namespace sk {
namespace config {

const char* version_string();

} // namespace config

// BOOST_PP_BOOL_true and BOOST_PP_BOOL_false provide true/false into BOOST_PP_BOOL
// I suggested to add it into <boost/preprocessor/logical/bool.hpp>
// TODO: remove BOOST_PP_BOOL_true and BOOST_PP_BOOL_false definitions

// #define BOOST_PP_BOOL_true 1
// #define BOOST_PP_BOOL_false 0

// #define SK_throw_pedantic_noreturn                            \
//    BOOST_PP_IF(BOOST_PP_BOOL(SK_OPTION_PEDANTIC_EXCEPTIONS), \
//                [[noreturn]], BOOST_PP_EMPTY())

#if (BOOST_COMP_CLANG != BOOST_VERSION_NUMBER_NOT_AVAILABLE)

// Clang wants to mark that function [[noreturn]]
// But it will make whole code after throw_pedantic call unreachable

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#endif // BOOST_COMP_CLANG

inline void throw_pedantic(std::exception const& ex) {
    using namespace sk::config;
    if constexpr (is_enabled<BuildOptionsEnum::pedantic_exceptions>) {
        throw ex;
    }
}

#if (BOOST_COMP_CLANG != BOOST_VERSION_NUMBER_NOT_AVAILABLE)

#pragma clang diagnostic pop

#endif // BOOST_COMP_CLANG

// #undef SK_throw_pedantic_noreturn

} // namespace sk

#endif // SK_CONFIG_HPP
