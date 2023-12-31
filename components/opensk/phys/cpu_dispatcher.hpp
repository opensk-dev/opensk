#ifndef SK_PHYSICS_CPU_DISPATCHER_HPP
#define SK_PHYSICS_CPU_DISPATCHER_HPP

#include <physx/task/PxCpuDispatcher.h>

#include <tbb/task_arena.h>

#include <cstdint>

namespace sk {

class PhysicsCpuDispatcher : public physx::PxCpuDispatcher {
  public:
    explicit PhysicsCpuDispatcher(tbb::task_arena& task_arena);

    ~PhysicsCpuDispatcher() override = default;

    PhysicsCpuDispatcher(PhysicsCpuDispatcher const& other) = delete;

    PhysicsCpuDispatcher& operator=(PhysicsCpuDispatcher const& other) = delete;

    PhysicsCpuDispatcher(PhysicsCpuDispatcher&& other) noexcept = default;

    PhysicsCpuDispatcher& operator=(PhysicsCpuDispatcher&& other) noexcept = delete;

    void submitTask(physx::PxBaseTask& task) override;

    [[nodiscard]] std::uint32_t getWorkerCount() const override;

  private:
    tbb::task_arena& task_arena_;
};
}// namespace sk

#endif// SK_PHYSICS_CPU_DISPATCHER_HPP
