#include <phys/error_callback.hpp>
#include <phys/exceptions.hpp>

#include <spdlog/spdlog.h>

namespace sk {
void PhysicsErrorCallback::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) {

    using spdlog::level::level_enum;
    auto log_level = level_enum::debug;
    std::string level_string = "";

    switch (code) {
    case physx::PxErrorCode::eNO_ERROR: {
        level_string = "no error";
        log_level = level_enum::debug;
        break;
    }
    case physx::PxErrorCode::eDEBUG_INFO: {
        level_string = "debug info";
        log_level = level_enum::debug;
        break;
    }
    case physx::PxErrorCode::eDEBUG_WARNING: {
        level_string = "debug warning";
        log_level = level_enum::debug;
        break;
    }
    case physx::PxErrorCode::eINVALID_PARAMETER: {
        level_string = "invalid parameter";
        log_level = level_enum::err;
        break;
    }
    case physx::PxErrorCode::eINVALID_OPERATION: {
        level_string = "invalid operation";
        log_level = level_enum::err;
        break;
    }
    case physx::PxErrorCode::eOUT_OF_MEMORY: {
        level_string = "out of memory";
        log_level = level_enum::warn;
        break;
    }
    case physx::PxErrorCode::eINTERNAL_ERROR: {
        level_string = "internal error";
        log_level = level_enum::err;
        break;
    }
    case physx::PxErrorCode::eABORT: {
        level_string = "abort";
        log_level = level_enum::critical;
        break;
    }
    case physx::PxErrorCode::ePERF_WARNING: {
        level_string = "perf warning";
        log_level = level_enum::warn;
        break;
    }
    case physx::PxErrorCode::eMASK_ALL: {
        level_string = "unknown";
        log_level = level_enum::debug;
    }
    }

    spdlog::log(log_level, "Physics error callback report\n\t[{}] ({}:{})\n\t{}", level_string, file, line, message);

    if (code == physx::PxErrorCode::eABORT) {
        throw sk::exceptions::PhysicsAbort();
    }
}

} // namespace sk
