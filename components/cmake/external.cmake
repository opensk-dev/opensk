
set(Boost_NO_WARN_NEW_VERSIONS ON)
set(Boost_USE_MULTITHREADED ON)

set(sk_boost_required_components
    program_options
)

find_package(Boost 1.82 REQUIRED COMPONENTS ${sk_boost_required_components})

find_package(TBB REQUIRED)

find_package(unofficial-omniverse-physx-sdk REQUIRED)

find_package(spdlog 1.12 REQUIRED)

if(sk_profiling)
    find_package(Tracy REQUIRED)
else()
    add_subdirectory(dummy/dummy_Tracy)
endif()
