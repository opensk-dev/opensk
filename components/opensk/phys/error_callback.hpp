#ifndef SK_PHYSICS_ERROR_CALLBACK_HPP
#define SK_PHYSICS_ERROR_CALLBACK_HPP

#include <physx/foundation/PxErrorCallback.h>

namespace sk {

class PhysicsErrorCallback : public physx::PxErrorCallback {
  public:
    PhysicsErrorCallback() = default;

    ~PhysicsErrorCallback() override = default;

    PhysicsErrorCallback(PhysicsErrorCallback const& other) = default;

    PhysicsErrorCallback& operator=(PhysicsErrorCallback const& other) = default;

    PhysicsErrorCallback(PhysicsErrorCallback&& other) noexcept = default;

    PhysicsErrorCallback& operator=(PhysicsErrorCallback&& other) noexcept = default;

    void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
};
}// namespace sk

#endif// SK_PHYSICS_ERROR_CALLBACK_HPP
