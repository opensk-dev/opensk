# ifndef SK_PHYSICS_EXTENSIONS_HPP_
# define SK_PHYSICS_EXTENSIONS_HPP_

# include <stdexcept>

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

} // sk::exceptions

# endif // SK_PHYSICS_EXTENSIONS_HPP_
