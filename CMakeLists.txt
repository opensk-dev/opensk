cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(
    opensk
    DESCRIPTION "engine for skyrim"
    VERSION 0.0.0
    LANGUAGES CXX
)

option(sk_build_opensk "Build opensk executable" ON)
option(sk_build_tests "Build tests for opensk" OFF)
option(sk_pedantic_exceptions "Enable pedantic exceptions" OFF)
option(sk_debug_output "Enable debug output" OFF)
option(sk_profiling "Enable profiling tool" OFF)
option(sk_physics_debug "Enable physics debug tools" OFF)

if(sk_build_tests)
    # При подключении CTest выполняется enable_testing()
    # Это необходимо вызывать в root CMakeLists.txt для корректного выполнения workflow run-tests
    include(CTest)
endif()

add_subdirectory(components)
