
add_library(sk_test_settings INTERFACE)
target_compile_features(sk_test_settings INTERFACE cxx_std_23)
target_include_directories(sk_test_settings INTERFACE ${sk_sources_dir})

# for boost-test
find_package(Boost 1.82 REQUIRED COMPONENTS program_options unit_test_framework)
target_include_directories(sk_test_settings INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(sk_test_settings INTERFACE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()

add_executable(sk_test_read_options "test_read_options.cpp" "${sk_sources_dir}/read_options.hpp")
target_link_libraries(sk_test_read_options sk_test_settings Boost::program_options)
