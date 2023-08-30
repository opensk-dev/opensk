# ifndef SK_PHYSICS_ERROR_CALLBACK_HPP_
# define SK_PHYSICS_ERROR_CALLBACK_HPP_

# include <physx/foundation/PxErrorCallback.h>

namespace sk {

class PhysicsErrorCallback : public physx::PxErrorCallback {
public:
    PhysicsErrorCallback() = default;
    ~PhysicsErrorCallback() override = default;

    PhysicsErrorCallback(const PhysicsErrorCallback& other) = default;
    PhysicsErrorCallback& operator=(const PhysicsErrorCallback& other) = default;

    PhysicsErrorCallback(PhysicsErrorCallback&& other) noexcept = default;
    PhysicsErrorCallback& operator=(PhysicsErrorCallback&& other) noexcept = default;

    void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;

private:

};

} // sk

# endif // SK_PHYSICS_ERROR_CALLBACK_HPP_
