
add_library(sk_tests_setup INTERFACE)
target_link_libraries(sk_tests_setup INTERFACE opensk_lib)

# for boost-test
find_package(Boost 1.82 REQUIRED COMPONENTS unit_test_framework)
target_link_libraries(sk_tests_setup INTERFACE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()

add_executable(sk_test_read_options "test_read_options.cpp")
target_link_libraries(sk_test_read_options sk_tests_setup)
