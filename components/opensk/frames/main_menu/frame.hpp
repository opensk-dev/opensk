#ifndef SK_FRAMES_MAIN_MENU_FRAME_HPP_
#define SK_FRAMES_MAIN_MENU_FRAME_HPP_

#include <core/frame.hpp>
#include <frames/main_menu/hello_task.hpp>

namespace sk {

class MainMenuFrame : public Frame {
  public:
    MainMenuFrame() = default;

    ~MainMenuFrame() override = default;

    MainMenuFrame(MainMenuFrame const& other) = delete;

    MainMenuFrame& operator=(MainMenuFrame const& other) = delete;

    MainMenuFrame(MainMenuFrame&& other) noexcept = default;

    MainMenuFrame& operator=(MainMenuFrame&& other) noexcept = default;

    void initialize() override;

    void finalize() override;

    void on_enable() override;

    void on_disable() override;

  private:
    HelloTask hello_task_;
};
} // namespace sk

#endif // SK_FRAMES_MAIN_MENU_FRAME_HPP_
