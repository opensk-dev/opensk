cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(
    opensk
    DESCRIPTION "engine for skyrim"
    VERSION 0.0.0
    LANGUAGES CXX
)

option(sk_build_tests "Build tests for opensk" OFF)

add_subdirectory(components)
