# ifndef SK_CORE_TASK_HPP_
# define SK_CORE_TASK_HPP_

namespace sk {

class Task {
public:
    Task() = default;
    virtual ~Task() = default;

    Task(const Task& other) = default;
    Task& operator=(const Task& other) = default;

    Task(Task&& other) noexcept = default;
    Task& operator=(Task&& other) noexcept = default;

    virtual void execute() = 0;
    virtual void abort() {};
};

} // sk

# endif // SK_CORE_TASK_HPP_
