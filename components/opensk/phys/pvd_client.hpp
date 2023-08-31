# ifndef SK_PHYSICS_PVD_CLIENT_HPP_
# define SK_PHYSICS_PVD_CLIENT_HPP_

namespace physx {

class PxPvd;
class PxFoundation;

}

namespace sk::debug {

class PvdClient {
public:
    PvdClient() = default;
    ~PvdClient();

    PvdClient(const PvdClient& other) = delete;
    PvdClient& operator=(const PvdClient& other) = delete;

    PvdClient(PvdClient&& other) noexcept;
    PvdClient& operator=(PvdClient&& other) noexcept;

    void initialize(physx::PxFoundation& foundation);
    void finalize();

    [[nodiscard]] physx::PxPvd* get_pvd() const;

private:
    physx::PxPvd* pvd_ptr_ = nullptr;
};

} // sk::debug

# endif // SK_PHYSICS_PVD_CLIENT_HPP_