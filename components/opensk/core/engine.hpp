#ifndef SK_CORE_ENGINE_HPP
#define SK_CORE_ENGINE_HPP

#include <core/frame.hpp>
#include <core/runtime.hpp>
#include <core/settings.hpp>

#include <phys/manager.hpp>

#include <frames/main_menu/frame.hpp>

#include <optional>

namespace sk {

struct ConfigureOptions;

class Engine {
  public:
    explicit Engine(ConfigureOptions const& options);

    ~Engine();

    Engine(Engine const& other) = delete;

    Engine& operator=(Engine const& other) = delete;

    Engine(Engine&& other) noexcept = default;

    Engine& operator=(Engine&& other) noexcept = default;

    void run();

    Settings& get_settings();

    Runtime& get_runtime();

  private:
    Settings settings_;
    FrameHolder current_frame_{};
    MainMenuFrame main_menu_frame_{};
    std::optional<Runtime> runtime_{};
    std::optional<PhysicsManager> physics_manager_{};
};
}// namespace sk

#endif// SK_CORE_ENGINE_HPP
