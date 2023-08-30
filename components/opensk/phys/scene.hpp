# ifndef SK_PHYSICS_SCENE_HPP_
# define SK_PHYSICS_SCENE_HPP_

namespace sk {

class PhysicsScene {
public:
    PhysicsScene() = default;
    ~PhysicsScene() = default;

    PhysicsScene(const PhysicsScene& other) = default;
    PhysicsScene& operator=(const PhysicsScene& other) = default;

    PhysicsScene(PhysicsScene&& other) noexcept = default;
    PhysicsScene& operator=(PhysicsScene&& other) noexcept = default;

private:

};

} // sk

# endif // SK_PHYSICS_SCENE_HPP_
