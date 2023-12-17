#include <core/exceptions.hpp>
#include <format>
#include <thread>

namespace sk::exceptions {

// Common

BadAccess::BadAccess(std::string const& whats_exactly) : runtime_error(std::format("Bad access: {}", whats_exactly)) {
}

ThreadAssert::ThreadAssert() : BadAccess("Thread assert") {
}

// Frame

FrameBadAccess::FrameBadAccess(const char* details) : BadAccess(std::format("Frame lifecycle: {}", details)) {
}

// Engine

EngineInitializationFailure::EngineInitializationFailure(const char* message) : std::runtime_error(
        std::format("Engine initialization failed with an error: {}", message)) {
}

FailedToInitializeRuntime::FailedToInitializeRuntime() : EngineInitializationFailure("Couldn't initialize runtime") {
}

FailedToInitializePhysics::FailedToInitializePhysics() : EngineInitializationFailure("Couldn't initialize physics") {
}

// Runtime

RuntimeInitializationFailure::RuntimeInitializationFailure(std::string const& message) : std::runtime_error(
        std::format("Runtime initialization failed with an error: {}", message)) {
}

UnsupportedHardwareConstraint::UnsupportedHardwareConstraint(const char* constraint) : RuntimeInitializationFailure(
        std::format("Unsupported hardware constraint: {}", constraint)) {
}
}// namespace sk::exceptions
