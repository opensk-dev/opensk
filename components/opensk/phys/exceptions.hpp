#ifndef SK_PHYSICS_EXTENSIONS_HPP
#define SK_PHYSICS_EXTENSIONS_HPP

#include <stdexcept>

namespace sk::exceptions {

class PhysicsInitializationFailure : public std::runtime_error {
  public:
    explicit PhysicsInitializationFailure(const char* message);
};

class FailedToCreateFoundation : public PhysicsInitializationFailure {
  public:
    FailedToCreateFoundation();
};

class FailedToCreatePhysicsInstance : public PhysicsInitializationFailure {
  public:
    FailedToCreatePhysicsInstance();
};

class PhysicsAbort : public std::runtime_error {
  public:
    explicit PhysicsAbort();
};
}// namespace sk::exceptions

#endif// SK_PHYSICS_EXTENSIONS_HPP
