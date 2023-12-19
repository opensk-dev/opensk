#ifndef SK_PHYSICS_SCENE_HPP
#define SK_PHYSICS_SCENE_HPP

namespace sk {

class PhysicsScene {
  public:
    PhysicsScene() = default;

    ~PhysicsScene() = default;

    PhysicsScene(PhysicsScene const& other) = default;

    PhysicsScene& operator=(PhysicsScene const& other) = default;

    PhysicsScene(PhysicsScene&& other) noexcept = default;

    PhysicsScene& operator=(PhysicsScene&& other) noexcept = default;

  private:
};
}// namespace sk

#endif// SK_PHYSICS_SCENE_HPP
