# ifndef SK_CORE_RUNTIME_ARENA_HPP_
# define SK_CORE_RUNTIME_ARENA_HPP_

# include <core/task.hpp>
# include <tbb/concurrent_queue.h>

# include <functional>
# include <optional>
# include <thread>

namespace sk {

class RuntimeArena {
public:
    RuntimeArena();

    struct Managed {};
    explicit RuntimeArena(const Managed&);

    ~RuntimeArena();

    RuntimeArena(const RuntimeArena& other) = delete;
    RuntimeArena& operator=(const RuntimeArena& other) = delete;

    RuntimeArena(RuntimeArena&& other) noexcept = default;
    RuntimeArena& operator=(RuntimeArena&& other) noexcept = default;

    void push_task(Task* task);

    void start();
    void stop();
    void capture();

private:
    void working_loop();

    struct ControlBlock {
        explicit ControlBlock(const std::function<void()>& working_loop);
        explicit ControlBlock(const Managed&) {};

        bool on_fire() const;

        std::mutex mtx{};
        std::atomic_bool is_working = false;
        std::optional<std::thread> working_thread{};
        tbb::concurrent_bounded_queue<Task*> tasks_queue{};
    };

    std::unique_ptr<ControlBlock> control_block_ptr_{};
};

} // sk

# endif // SK_CORE_RUNTIME_ARENA_HPP_
