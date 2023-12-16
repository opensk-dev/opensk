#include <phys/pvd_client.hpp>

#include <spdlog/spdlog.h>

#include <physx/foundation/PxFoundation.h>

#include <physx/pvd/PxPvd.h>
#include <physx/pvd/PxPvdTransport.h>

namespace sk::debug {

#ifdef SK_ENABLE_PHYSX_PVD_CLIENT

void PvdClient::initialize(physx::PxFoundation &foundation) {
    pvd_ptr_ = physx::PxCreatePvd(foundation);
    physx::PxPvdTransport *transport = physx::PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
    pvd_ptr_->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
    if (pvd_ptr_->isConnected()) {
        spdlog::debug("PVD connected");
    }
}

void PvdClient::finalize() {
    if (pvd_ptr_) {
        auto *transport = pvd_ptr_->getTransport();
        pvd_ptr_->release();
        pvd_ptr_ = nullptr;
        transport->release();
    }
}

PvdClient::PvdClient(PvdClient &&other) noexcept : pvd_ptr_(other.pvd_ptr_) {
    other.pvd_ptr_ = nullptr;
}

PvdClient &PvdClient::operator=(PvdClient &&other) noexcept {
    if (this != &other) {
        pvd_ptr_ = other.pvd_ptr_;
        other.pvd_ptr_ = nullptr;
    }
    return *this;
}

#else// SK_ENABLE_PHYSX_PVD_CLIENT

void PvdClient::initialize(physx::PxFoundation&) {
    spdlog::debug("PhysX PVD client disabled\n");
}

void PvdClient::finalize() {
}

PvdClient::PvdClient(PvdClient&&) noexcept: pvd_ptr_() {
}

PvdClient& PvdClient::operator=(PvdClient&&) noexcept {
    return *this;
}

#endif// SK_ENABLE_PHYSX_PVD_CLIENT

PvdClient::~PvdClient() {
    finalize();
}

physx::PxPvd* PvdClient::get_pvd() const {
    return pvd_ptr_;
}

} // namespace sk::debug
