
set(sk_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/opensk")
set(sk_resources_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(sk_output_dir "${CMAKE_BINARY_DIR}/out")

# add_subdirectory(data_driver)

include(cmake/external.cmake)
include(cmake/opensk.cmake)

if(sk_build_tests)
    add_subdirectory(tests)
endif()