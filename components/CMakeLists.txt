set(Boost_NO_WARN_NEW_VERSIONS 1)

set(sk_sources_dir "${CMAKE_CURRENT_SOURCE_DIR}/engine")
set(sk_resources_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources")

add_subdirectory(data_driver)
add_subdirectory(engine)

if(sk_build_tests)
    add_subdirectory(tests)
endif()