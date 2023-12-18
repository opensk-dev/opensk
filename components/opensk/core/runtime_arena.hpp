#ifndef SK_CORE_RUNTIME_ARENA_HPP
#define SK_CORE_RUNTIME_ARENA_HPP

#include <core/task.hpp>
#include <tbb/concurrent_queue.h>

#include <functional>
#include <optional>
#include <thread>

namespace sk {

class RuntimeArena {
  public:
    RuntimeArena();

    struct Managed {};

    explicit RuntimeArena(Managed const&);

    ~RuntimeArena();

    RuntimeArena(RuntimeArena const& other) = delete;

    RuntimeArena& operator=(RuntimeArena const& other) = delete;

    RuntimeArena(RuntimeArena&& other) noexcept = default;

    RuntimeArena& operator=(RuntimeArena&& other) noexcept = default;

    void push_task(Task* task);

    void start();

    void stop();

    void capture();

    void stop_in_future();

  private:
    void working_loop();

    struct Control {
        explicit Control(std::function<void()> const& working_loop);

        explicit Control(Managed const&) {
        }

        bool on_fire() const;

        std::mutex mtx{};
        std::atomic_bool is_working = false;
        std::atomic_bool is_should_exit = false;
        std::optional<std::thread> working_thread{};
        tbb::concurrent_bounded_queue<Task*> tasks_queue{};
    };

    std::unique_ptr<Control> control_ptr_{};
};
}// namespace sk

#endif// SK_CORE_RUNTIME_ARENA_HPP
