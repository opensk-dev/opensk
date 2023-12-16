#include <config.hpp>
#include <phys/exceptions.hpp>
#include <phys/manager.hpp>

#include <spdlog/spdlog.h>
#include <tracy/Tracy.hpp>

#include <physx/PxPhysics.h>
#include <physx/PxScene.h>
#include <physx/common/PxTolerancesScale.h>
#include <physx/extensions/PxDefaultAllocator.h>
#include <physx/foundation/PxFoundation.h>
#include <physx/foundation/PxPhysicsVersion.h>

namespace sk {

PhysicsManager::PhysicsManager(tbb::task_arena& task_arena) {
    ZoneScopedNC("initialize physics", tracy::Color::MediumSpringGreen);
    error_callback_ptr_ = std::make_unique<PhysicsErrorCallback>();
    allocator_callback_ptr_ = std::make_unique<physx::PxDefaultAllocator>();
    foundation_ptr_ = PxCreateFoundation(PX_PHYSICS_VERSION, *allocator_callback_ptr_, *error_callback_ptr_);
    if (!foundation_ptr_) {
        foundation_ptr_ = nullptr;
        throw sk::exceptions::FailedToCreateFoundation();
    }
    if constexpr (sk::config::is_enabled<sk::config::BuildOptionsEnum::physics_debug>) {
        pvd_client_.initialize(*foundation_ptr_);
    }
    physics_ptr_ =
        PxCreatePhysics(PX_PHYSICS_VERSION, *foundation_ptr_, physx::PxTolerancesScale(), false, pvd_client_.get_pvd());
    if (!physics_ptr_) {
        physics_ptr_ = nullptr;
        throw sk::exceptions::FailedToCreatePhysicsInstance();
    }
    cpu_dispatcher_ptr_ = std::make_unique<PhysicsCpuDispatcher>(task_arena);
}

PhysicsManager::~PhysicsManager() {
    ZoneScopedNC("finalize physics", tracy::Color::MediumSpringGreen);
    if (physics_ptr_ != nullptr) {
        physics_ptr_->release();
        physics_ptr_ = nullptr;
    }
    pvd_client_.finalize();
    if (foundation_ptr_ != nullptr) {
        foundation_ptr_->release();
        foundation_ptr_ = nullptr;
    }
}

PhysicsManager::PhysicsManager(PhysicsManager&& other) noexcept:
    error_callback_ptr_(std::move(other.error_callback_ptr_)),
    cpu_dispatcher_ptr_(std::move(other.cpu_dispatcher_ptr_)),
    allocator_callback_ptr_(std::move(other.allocator_callback_ptr_)),
    foundation_ptr_(other.foundation_ptr_),
    physics_ptr_(other.physics_ptr_),
    pvd_client_(std::move(other.pvd_client_)) {
    other.foundation_ptr_ = nullptr;
    other.physics_ptr_ = nullptr;
}

PhysicsManager& PhysicsManager::operator=(PhysicsManager&& other) noexcept {
    if (this != &other) {
        error_callback_ptr_ = std::move(other.error_callback_ptr_);
        allocator_callback_ptr_ = std::move(other.allocator_callback_ptr_);
        cpu_dispatcher_ptr_ = std::move(other.cpu_dispatcher_ptr_);
        pvd_client_ = std::move(other.pvd_client_);
        foundation_ptr_ = other.foundation_ptr_;
        other.foundation_ptr_ = nullptr;
        physics_ptr_ = other.physics_ptr_;
        other.physics_ptr_ = nullptr;
    }
    return *this;
}

} // namespace sk
