
add_library(compile_flags_setup INTERFACE)
target_compile_features(compile_flags_setup INTERFACE cxx_std_23)

if(sk_pedantic_warnings)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Set pedantic warnings for MSVC")
        target_compile_options(
            compile_flags_setup INTERFACE
            /W4
            /WX
            /wd4996 # Many standard functions have been marked as deprecated.
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Set pedantic warnings for GNU")
        target_compile_options(
            compile_flags_setup INTERFACE
            -Werror

            -Wall
            -Wextra
            -Wpedantic

            -Wno-comment
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Set pedantic warnings for Clang")
        target_compile_options(
            compile_flags_setup INTERFACE
            -Werror

            -Wall
            -Wextra
            -Wpedantic
            # -Weverything

            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-c++11-compat
            -Wno-c++11-compat-pedantic
            -Wno-c++14-compat
            -Wno-c++14-compat-pedantic
            -Wno-c++17-compat
            -Wno-c++17-compat-pedantic
            -Wno-c++20-compat
            -Wno-c++20-compat-pedantic
        )
    else()
        message(WARNING "Cannot set pedantic warnings: unsupported compiler")
    endif()
endif()