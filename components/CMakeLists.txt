
set(sk_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/opensk")
set(sk_resources_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(sk_output_dir "${CMAKE_BINARY_DIR}/out")

set(Boost_NO_WARN_NEW_VERSIONS ON)
set(Boost_USE_MULTITHREADED ON)

add_subdirectory(dummy)
add_subdirectory(data_driver)

add_library(opensk_lib STATIC)
add_subdirectory(opensk)

if(sk_build_tests)
    add_subdirectory(tests)
endif()