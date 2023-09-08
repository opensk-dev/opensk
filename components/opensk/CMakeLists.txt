
set(sk_gen_include_dir "${CMAKE_CURRENT_BINARY_DIR}/include/opensk")
configure_file("${sk_source_dir}/config_def.hpp.in" "${sk_gen_include_dir}/config_def.hpp")

set(
    sk_gen_headers
    "${sk_gen_include_dir}/config_def.hpp"
)

set(
    sk_sources
    "${sk_source_dir}/options.hpp"
    "${sk_source_dir}/options.cpp"
    "${sk_source_dir}/config.hpp"
    "${sk_source_dir}/config.cpp"

    "${sk_source_dir}/core/exceptions.hpp"
    "${sk_source_dir}/core/exceptions.cpp"
    "${sk_source_dir}/core/create.hpp"
    "${sk_source_dir}/core/engine.hpp"
    "${sk_source_dir}/core/engine.cpp"
    "${sk_source_dir}/core/frame.hpp"
    "${sk_source_dir}/core/frame.cpp"
    "${sk_source_dir}/core/settings.hpp"
    "${sk_source_dir}/core/settings.cpp"
    "${sk_source_dir}/core/task.hpp"
    "${sk_source_dir}/core/task.cpp"
    "${sk_source_dir}/core/runtime.hpp"
    "${sk_source_dir}/core/runtime.cpp"
    "${sk_source_dir}/core/runtime_arena.hpp"
    "${sk_source_dir}/core/runtime_arena.cpp"

    "${sk_source_dir}/phys/exceptions.hpp"
    "${sk_source_dir}/phys/exceptions.cpp"
    "${sk_source_dir}/phys/manager.hpp"
    "${sk_source_dir}/phys/manager.cpp"
    "${sk_source_dir}/phys/scene.hpp"
    "${sk_source_dir}/phys/scene.cpp"
    "${sk_source_dir}/phys/cpu_dispatcher.hpp"
    "${sk_source_dir}/phys/cpu_dispatcher.cpp"
    "${sk_source_dir}/phys/error_callback.hpp"
    "${sk_source_dir}/phys/error_callback.cpp"
    "${sk_source_dir}/phys/pvd_client.hpp"
    "${sk_source_dir}/phys/pvd_client.cpp"

    "${sk_source_dir}/math/rect.hpp"

    "${sk_source_dir}/frames/main_menu/frame.hpp"
    "${sk_source_dir}/frames/main_menu/frame.cpp"
    "${sk_source_dir}/frames/main_menu/hello_task.hpp"
    "${sk_source_dir}/frames/main_menu/hello_task.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sk_sources})
list(APPEND sk_sources ${sk_gen_headers})

target_sources(opensk_lib PUBLIC ${sk_sources})
target_compile_features(opensk_lib PUBLIC cxx_std_23)

include(GNUInstallDirs)

target_include_directories(
    opensk_lib PUBLIC
    "$<BUILD_INTERFACE:${sk_source_dir}>"
    "$<BUILD_INTERFACE:${sk_gen_include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(opensk_lib PUBLIC opensk::data)

find_package(Boost 1.82 REQUIRED COMPONENTS program_options)
target_link_libraries(opensk_lib PUBLIC ${Boost_LIBRARIES})
target_include_directories(opensk_lib PUBLIC "$<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>")

find_package(TBB REQUIRED)
target_link_libraries(opensk_lib PUBLIC TBB::tbb)

find_package(unofficial-omniverse-physx-sdk REQUIRED)
target_link_libraries(opensk_lib PUBLIC unofficial::omniverse-physx-sdk::sdk)

find_package(spdlog 1.12 REQUIRED)
target_link_libraries(opensk_lib PUBLIC spdlog::spdlog)

if(sk_profiling)
    find_package(Tracy REQUIRED)
    target_link_libraries(opensk_lib PUBLIC Tracy::TracyClient)
    target_compile_definitions(
        opensk_lib
        PUBLIC TRACY_ENABLE
        PUBLIC SK_ENABLE_PROFILING
    )
else()
    target_link_libraries(opensk_lib PUBLIC dummy_Tracy)
endif()

if(sk_physics_debug)
    target_compile_definitions(
        opensk_lib
        PUBLIC SK_ENABLE_PHYSICS_DEBUG
        PUBLIC SK_ENABLE_PHYSX_PVD_CLIENT
    )
endif()

if(sk_debug_output)
    target_compile_definitions(
        opensk_lib
        PUBLIC SK_ENABLE_DEBUG_OUTPUT
    )
endif()

if(sk_pedantic_exceptions)
    target_compile_definitions(
        opensk_lib
        PUBLIC SK_ENABLE_PEDANTIC_EXCEPTIONS
    )
endif()

if(sk_build_opensk)
    add_executable(opensk "${sk_source_dir}/main.cpp"
        math/point.hpp)
    target_link_libraries(opensk opensk_lib)

    set_target_properties(
        opensk PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        ARCHIVE_OUTPUT_DIRECTORY "${sk_output_dir}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${sk_output_dir}"
        RUNTIME_OUTPUT_DIRECTORY "${sk_output_dir}"
    )

    add_custom_target(
        sk_copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${sk_resources_dir} $<TARGET_FILE_DIR:opensk>
        COMMENT "copying resources"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    add_dependencies(opensk sk_copy_resources)
endif()