
add_library(dummy_Tracy INTERFACE)
add_library(Tracy::TracyClient ALIAS dummy_Tracy)

target_sources(dummy_Tracy INTERFACE
    tracy/Tracy.hpp
    common/TracyColor.hpp
    common/TracySystem.hpp
    common/TracyApi.h
)

target_include_directories(dummy_Tracy INTERFACE "./")
