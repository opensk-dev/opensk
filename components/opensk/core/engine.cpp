# include <core/engine.hpp>
# include <core/create.hpp>
# include <core/exceptions.hpp>

# include <options.hpp>

# include <tracy/Tracy.hpp>

namespace sk {

Engine::Engine(const ConfigureOptions& options)
    : settings_(options.settings_path) {
    ZoneScopedNC("initialize engine", tracy::Color::Aqua);
    FrameHolder::set_engine_ptr(this);
    settings_.load("hardware.ini", "hardware");
    auto hardware_concurrency = settings_.get<std::uint32_t>("hardware.cpu.concurrency");
    create(runtime_, hardware_concurrency);
    if (!runtime_) {
        throw sk::exceptions::FailedToInitializeRuntime();
    }
}

void Engine::run() {
    main_menu_frame_.initialize();
    current_frame_ = &main_menu_frame_;
    runtime_->get_main_arena().capture();
    spdlog::info("finish run");
}

Engine::~Engine() {
    main_menu_frame_.finalize();
}

Settings& Engine::get_settings() {
    return settings_;
}

Runtime& Engine::get_runtime() {
    return runtime_.value();
}

} // sk
