
add_executable(opensk "main.cpp")

set_target_properties(
    opensk PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_link_libraries(opensk opensk_lib opensk::data)

set(sk_gen_include_dir "${CMAKE_CURRENT_BINARY_DIR}/include/opensk")
configure_file("${sk_source_dir}/config.hpp.in" "${sk_gen_include_dir}/config.hpp")

set(
    sk_gen_headers
    "${sk_gen_include_dir}/config.hpp"
)

set(
    sk_sources
    "${sk_source_dir}/read_options.hpp"
    "${sk_source_dir}/read_options.cpp"
    "${sk_source_dir}/version.hpp"
    "${sk_source_dir}/version.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sk_sources})
list(APPEND sk_sources ${sk_gen_headers})

target_sources(opensk_lib INTERFACE ${sk_sources})
target_compile_features(opensk_lib INTERFACE cxx_std_23)

include(GNUInstallDirs)

target_include_directories(
    opensk_lib INTERFACE
    "$<BUILD_INTERFACE:${sk_source_dir}>"
    "$<BUILD_INTERFACE:${sk_gen_include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(Boost 1.82 REQUIRED COMPONENTS program_options)
target_link_libraries(opensk_lib INTERFACE Boost::program_options)

add_custom_target(
    sk_copy_resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${sk_resources_dir} ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "copying resources"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(opensk sk_copy_resources)
