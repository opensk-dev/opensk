cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(
    opensk
    DESCRIPTION "engine for skyrim"
    VERSION 0.0.0
    LANGUAGES CXX
)

option(sk_build_tests "Build tests for opensk" OFF)
option(sk_pedantic_exceptions "Enable pedantic exceptions" OFF)
option(sk_debug_output "Enable debug output" OFF)
option(sk_profiling "Enable profiling tool" OFF)
option(sk_physics_debug "Enable physics debug tools" OFF)

add_subdirectory(components)
