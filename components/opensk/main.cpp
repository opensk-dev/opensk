#include <config.hpp>
#include <options.hpp>

#include <core/create.hpp>
#include <core/engine.hpp>

#include <spdlog/spdlog.h>
#include <tracy/Tracy.hpp>

static void enable_debug_logging() {
    using sk::config::BuildOptionsEnum;
    if constexpr (sk::config::is_enabled<BuildOptionsEnum::debug_output>) {
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("enable profiling: {}", sk::config::is_enabled<BuildOptionsEnum::profiling>);
        spdlog::debug("enable physics debug: {}", sk::config::is_enabled<BuildOptionsEnum::physics_debug>);
    }
}

int main(int argc, const char* argv[]) {
    ZoneScopedNC("main", tracy::Color::BlueViolet);

    enable_debug_logging();

    auto options = sk::read_options(argc, argv);
    if (!options) {
        return 0;
    }

    auto engine = sk::create<sk::Engine>(options.value());
    if (!engine) {
        return -1;
    }

    engine->run();

    return 0;
}
