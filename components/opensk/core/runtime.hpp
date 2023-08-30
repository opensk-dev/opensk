# ifndef SK_CORE_RUNTIME_HPP_
# define SK_CORE_RUNTIME_HPP_

# include <core/runtime_arena.hpp>

# include <cstdint>

namespace sk {

class Task;

class Runtime {
public:
    explicit Runtime(std::uint32_t concurrency);

    Runtime(const Runtime& other) = delete;
    Runtime& operator=(const Runtime& other) = delete;

    Runtime(Runtime&& other) noexcept = default;
    Runtime& operator=(Runtime&& other) noexcept = default;

    enum class ArenasEnum {
        main,
    };

    void push_task(ArenasEnum arena, Task* task);
    void abort();

    [[nodiscard]] RuntimeArena& get_main_arena();

private:
    RuntimeArena main_arena_{RuntimeArena::Managed{}};
};

} // sk

# endif // SK_CORE_RUNTIME_HPP_
