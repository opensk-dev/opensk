# define BOOST_TEST_MAIN
# include <boost/test/unit_test.hpp>

# include <read_options.hpp>

BOOST_AUTO_TEST_SUITE(read_options_test_suite)

BOOST_AUTO_TEST_CASE(check_default_behaviour) {
    int argc = 2;
    const char* argv[] = {
        "Z:/invalid_path",
        "--help",
    };
    auto options = sk::read_options(argc, argv);
    BOOST_REQUIRE(options.has_value() == false);
}

BOOST_AUTO_TEST_SUITE_END()