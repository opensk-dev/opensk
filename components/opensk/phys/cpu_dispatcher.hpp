# ifndef SK_PHYSICS_CPU_DISPATCHER_HPP_
# define SK_PHYSICS_CPU_DISPATCHER_HPP_

# include <physx/task/PxCpuDispatcher.h>

# include <tbb/task_arena.h>

# include <cstdint>

namespace sk {

class PhysicsCpuDispatcher : public physx::PxCpuDispatcher {
public:
    explicit PhysicsCpuDispatcher(tbb::task_arena& task_arena);
    ~PhysicsCpuDispatcher() override = default;

    PhysicsCpuDispatcher(const PhysicsCpuDispatcher& other) = delete;
    PhysicsCpuDispatcher& operator=(const PhysicsCpuDispatcher& other) = delete;

    PhysicsCpuDispatcher(PhysicsCpuDispatcher&& other) noexcept = default;
    PhysicsCpuDispatcher& operator=(PhysicsCpuDispatcher&& other) noexcept = delete;

    void submitTask(physx::PxBaseTask& task) override;
    [[nodiscard]] std::uint32_t getWorkerCount() const override;

private:
    tbb::task_arena& task_arena_;
};

} // sk

# endif // SK_PHYSICS_CPU_DISPATCHER_HPP_
