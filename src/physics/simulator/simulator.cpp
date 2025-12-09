#include "physics/simulator/simulator.hpp"

#include <cstddef>

#include <physics/vector/vector.hpp>
#include <physics/units/quantity.hpp>

namespace physics::simulator {

void Simulator::ResetAccelerations() {
  for (auto& obj : objects_) {
    for (std::size_t i = 0; i < 3; ++i) {
      obj.acceleration[i] = units::Acceleration{0.0};
    }
  }
}

void Simulator::ApplyGravity() {
  const std::size_t n = objects_.size();
  if (n < 2) {
    return;
  }

  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i + 1; j < n; ++j) {
      auto fij = objects_[i].GravitationalForceVector(objects_[j]);

      objects_[i].ApplyForce(fij);

      vector::Vector<units::Force, 3> fji{};
      for (std::size_t k = 0; k < 3; ++k) {
        fji[k] = units::Force{-fij[k].value};
      }
      objects_[j].ApplyForce(fji);
    }
  }
}

void Simulator::HandleElasticCollision(object::Object& a, object::Object& b) {
  using physics::units::Length;
  using physics::units::Speed;
  using physics::vector::Vector;

  Vector<Length, 3> delta = b.position - a.position;
  double dist = vector::Norm(delta).value;

  constexpr double kEps = 1e-9;
  if (dist < kEps) {
    dist = kEps;
  }

  auto n = vector::Normalize(delta);

  Vector<Speed, 3> dv = b.speed - a.speed;
  double rel_vel = vector::Dot(dv, n).value;

  if (rel_vel >= 0.0) {
    return;
  }

  double m_a = a.weight.value;
  double m_b = b.weight.value;
  double inv_a = 1.0 / m_a;
  double inv_b = 1.0 / m_b;

  constexpr double kRestitution = 1.0;
  double j = -(1.0 + kRestitution) * rel_vel / (inv_a + inv_b);

  for (int k = 0; k < 3; ++k) {
    double nk = n[k].value;
    a.speed[k].value -= j * inv_a * nk;
    b.speed[k].value += j * inv_b * nk;
  }

  double overlap = collision_distance_.value - dist;
  if (overlap > 0.0) {
    double total_mass = m_a + m_b;
    double share_a = m_b / total_mass;
    double share_b = m_a / total_mass;

    for (int k = 0; k < 3; ++k) {
      double nk = n[k].value;
      a.position[k].value -= share_a * overlap * nk;
      b.position[k].value += share_b * overlap * nk;
    }
  }
}

void Simulator::HandleCollisions() {
  for (size_t i = 0; i < objects_.size(); ++i) {
    for (size_t j = i + 1; j < objects_.size(); ++j) {
      auto& a = objects_[i];
      auto& b = objects_[j];

      double dist = a.DistanceTo(b).value;

      if (dist <= collision_distance_.value) {
        HandleElasticCollision(a, b);
      }
    }
  }
}

void Simulator::Step(units::Time dt) {
  ResetAccelerations();

  if (use_gravity_) {
    ApplyGravity();
  }

  for (auto& obj : objects_) {
    obj.Update(dt);
  }

  HandleCollisions();
}

}  // namespace physics::simulator