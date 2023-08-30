# include <phys/exceptions.hpp>
# include <format>

namespace sk::exceptions {

PhysicsInitializationFailure::PhysicsInitializationFailure(const char* message)
    : std::runtime_error(std::format("Physics initialization failed with an error: {}", message)) {}

FailedToCreateFoundation::FailedToCreateFoundation()
    : PhysicsInitializationFailure("Couldn't create foundation") {}

FailedToCreatePhysicsInstance::FailedToCreatePhysicsInstance()
    : PhysicsInitializationFailure("Couldn't create physics instance") {}

PhysicsAbort::PhysicsAbort()
    : std::runtime_error("Physics abort had been called") {}

} // sk::exceptions