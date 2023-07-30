
set(sk_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/opensk")
set(sk_output_dir "${CMAKE_CURRENT_BINARY_DIR}/out")
set(sk_resources_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SK_DATA_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SK_DATA_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SK_DATA_OUTPUT_DIRECTORY})

add_library(opensk_lib INTERFACE)

# Disable boost warning
set(Boost_NO_WARN_NEW_VERSIONS 1)

add_subdirectory(data_driver)
add_subdirectory(opensk)

if(sk_build_tests)
    add_subdirectory(tests)
endif()