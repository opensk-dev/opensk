#ifndef SK_CONFIG_DEF_HPP_
#define SK_CONFIG_DEF_HPP_

#define SK_VERSION_STRING "0.0.0"

#ifdef SK_ENABLE_PEDANTIC_EXCEPTIONS
#define SK_PEDANTIC_EXCEPTIONS true
#else
#define SK_PEDANTIC_EXCEPTIONS false
#endif

#ifdef SK_ENABLE_DEBUG_OUTPUT
#define SK_DEBUG_OUTPUT true
#else
#define SK_DEBUG_OUTPUT false
#endif

#ifdef SK_ENABLE_PROFILING
#define SK_PROFILING true
#else
#define SK_PROFILING false
#endif

#ifdef SK_ENABLE_PHYSICS_DEBUG
#define SK_PHYSICS_DEBUG true
#else
#define SK_PHYSICS_DEBUG false
#endif

#endif// SK_CONFIG_DEF_HPP_
