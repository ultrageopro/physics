#pragma once

#include <vector>

#include <physics/object/object.hpp>
#include <physics/units/quantity.hpp>

namespace physics::simulator {

class Simulator {
 public:
  Simulator() = default;

  explicit Simulator(units::Length collision_distance) : collision_distance_(collision_distance) {
  }

  Simulator(std::vector<object::Object> objects, units::Length collision_distance)
      : objects_(std::move(objects)), collision_distance_(collision_distance) {
  }

  void EnableGravity(bool enabled) {
    use_gravity_ = enabled;
  }
  bool GravityEnabled() const {
    return use_gravity_;
  }

  std::vector<object::Object>& Objects() {
    return objects_;
  }
  const std::vector<object::Object>& Objects() const {
    return objects_;
  }

  void AddObject(const object::Object& obj) {
    objects_.push_back(obj);
  }

  void Step(units::Time dt);

 private:
  std::vector<object::Object> objects_;
  bool use_gravity_ = true;
  units::Length collision_distance_{units::Length{0.0}};

  void HandleElasticCollision(object::Object& a, object::Object& b);
  void ResetAccelerations();
  void ApplyGravity();
  void HandleCollisions();
};

}  // namespace physics::simulator