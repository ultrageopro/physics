#include <physics/constants.hpp>
#include <physics/formulas/gravity.hpp>
#include <physics/units/quantity.hpp>

namespace physics::gravity {

units::Force GravitationalForce(units::Mass m1, units::Mass m2, units::Length distance) {
  return physics::constants::kG * m1 * m2 / (distance * distance);
}

units::Acceleration GravitationalAcceleration(units::Mass mass, units::Length radius) {
  return physics::constants::kG * mass / (radius * radius);
}

units::Energy GravitationalPotentialEnergy(units::Mass m1, units::Mass m2, units::Length distance) {
  return units::Energy{-physics::constants::kG.value * m1.value * m2.value / distance.value};
}

units::Speed EscapeVelocity(units::Mass planet, units::Length radius) {
  return units::Speed{std::sqrt(physics::constants::kG.value * planet.value / radius.value)};
}

units::Speed OrbitalVelocity(units::Mass planet, units::Length radius) {
  return units::Speed{std::sqrt(physics::constants::kG.value * planet.value / radius.value)};
}

}  // namespace physics::gravity