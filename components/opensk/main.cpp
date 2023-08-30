# include <options.hpp>
# include <config.hpp>

# include <core/create.hpp>
# include <core/engine.hpp>

# include <spdlog/spdlog.h>
# include <tracy/Tracy.hpp>

# include <core/runtime_arena.hpp>
# include <frames/main_menu/hello_task.hpp>

# include <thread>

void enable_debug_logging() {
    using sk::config::BuildOptionsEnum;
    if (sk::config::is_enabled<BuildOptionsEnum::debug_output>()) {
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("enable profiling: {}", sk::config::is_enabled<BuildOptionsEnum::profiling>());
        spdlog::debug("enable physics debug: {}", sk::config::is_enabled<BuildOptionsEnum::physics_debug>());
    }
}

int main(int argc, const char* argv[]) {
    ZoneScopedNC("main", tracy::Color::BlueViolet);

    enable_debug_logging();

    auto options = sk::read_options(argc, argv);
    if (!options) return 0;

    auto engine = sk::create<sk::Engine>(options.value());
    if (!engine) return -1;

    engine->run();

    return 0;
}
