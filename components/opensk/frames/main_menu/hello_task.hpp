#ifndef SK_FRAMES_MAIN_MENU_HELLO_TASK_HPP_
#define SK_FRAMES_MAIN_MENU_HELLO_TASK_HPP_

#include <core/task.hpp>

namespace sk {

class HelloTask : public Task {
  public:
    HelloTask() = default;

    ~HelloTask() override = default;

    HelloTask(HelloTask const&) = default;

    void execute() override;
};
} // namespace sk

#endif // SK_FRAMES_MAIN_MENU_HELLO_TASK_HPP_
