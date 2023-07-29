
set(
    sk_sources
    "main.cpp"
    "read_options.hpp"
)

add_executable(opensk ${sk_sources})
target_include_directories(opensk PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(opensk PUBLIC cxx_std_23)

add_custom_target(
    sk_copy_resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${sk_resources_dir} ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "copying resources"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(opensk sk_copy_resources)

target_link_libraries(opensk opensk::data)

find_package(Boost 1.82 REQUIRED COMPONENTS program_options)
target_link_libraries(opensk Boost::program_options)
