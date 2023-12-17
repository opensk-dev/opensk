#ifndef SK_CORE_EXCEPTIONS_HPP_
#define SK_CORE_EXCEPTIONS_HPP_

#include <stdexcept>

namespace sk::exceptions {

// Common

class BadAccess : public std::runtime_error {
  public:
    explicit BadAccess(std::string const& whats_exactly);
};

class ThreadAssert : public BadAccess {
  public:
    ThreadAssert();
};

// Frame

class FrameBadAccess : public BadAccess {
  public:
    explicit FrameBadAccess(const char* details);
};

// Engine

class EngineInitializationFailure : public std::runtime_error {
  public:
    explicit EngineInitializationFailure(const char* message);
};

class FailedToInitializeRuntime : public EngineInitializationFailure {
  public:
    FailedToInitializeRuntime();
};

class FailedToInitializePhysics : public EngineInitializationFailure {
  public:
    FailedToInitializePhysics();
};

// Runtime

class RuntimeInitializationFailure : public std::runtime_error {
  public:
    explicit RuntimeInitializationFailure(std::string const& message);
};

class UnsupportedHardwareConstraint : public RuntimeInitializationFailure {
  public:
    explicit UnsupportedHardwareConstraint(const char* constraint);
};
} // namespace sk::exceptions

#endif // SK_CORE_EXCEPTIONS_HPP_
