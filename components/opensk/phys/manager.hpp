#ifndef SK_PHYSICS_MANAGER_HPP
#define SK_PHYSICS_MANAGER_HPP

#include <phys/cpu_dispatcher.hpp>
#include <phys/error_callback.hpp>
#include <phys/pvd_client.hpp>

#include <physx/foundation/PxAllocatorCallback.h>

#include <tbb/task_arena.h>

#include <memory>
#include <optional>

namespace physx {

class PxFoundation;

class PxPhysics;
}// namespace physx

namespace sk {

class PhysicsManager {
  public:
    explicit PhysicsManager(tbb::task_arena& task_arena);

    ~PhysicsManager();

    PhysicsManager(PhysicsManager const& other) = delete;

    PhysicsManager& operator=(PhysicsManager const& other) = delete;

    PhysicsManager(PhysicsManager&& other) noexcept;

    PhysicsManager& operator=(PhysicsManager&& other) noexcept;

  private:
    std::unique_ptr<PhysicsErrorCallback> error_callback_ptr_ = nullptr;
    std::unique_ptr<PhysicsCpuDispatcher> cpu_dispatcher_ptr_ = nullptr;
    std::unique_ptr<physx::PxAllocatorCallback> allocator_callback_ptr_ = nullptr;
    physx::PxFoundation* foundation_ptr_ = nullptr;
    physx::PxPhysics* physics_ptr_ = nullptr;
    sk::debug::PvdClient pvd_client_{};
};
}// namespace sk

#endif// SK_PHYSICS_MANAGER_HPP
