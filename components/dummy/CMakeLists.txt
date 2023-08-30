
add_library(dummy_Tracy INTERFACE)

target_sources(
    dummy_Tracy INTERFACE
    ./dummy_tracy_include/tracy/Tracy.hpp
    ./dummy_tracy_include/common/TracyColor.hpp
    ./dummy_tracy_include/common/TracySystem.hpp
    ./dummy_tracy_include/common/TracyApi.h
)

target_include_directories(dummy_Tracy INTERFACE ./dummy_tracy_include)
