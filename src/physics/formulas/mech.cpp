#include <physics/units/quantity.hpp>

namespace physics::mech {

units::Energy KineticEnergy(units::Weight mass, units::Speed speed) {
  return mass * speed * speed / 2.0;
}

units::Energy PotentialEnergy(units::Weight mass, units::Acceleration g, units::Length height) {
  return mass * g * height;
}

units::Force NewtonSecondLaw(units::Weight mass, units::Acceleration accel) {
  return mass * accel;
}

units::Speed AverageSpeed(units::Length distance, units::Time time) {
  return distance / time;
}

units::Length UniformMotion(units::Length initial, units::Speed speed, units::Time time) {
  return initial + speed * time;
}

units::Length AcceleratedMotion(units::Length initial, units::Speed v0, units::Acceleration a, units::Time t) {
  return initial + v0 * t + a * t * t / 2.0;
}

units::Quantity<0, 1, 1> Momentum(units::Weight mass, units::Speed speed) {
  return units::Quantity<0, 1, 1>{mass.value * speed.value};
}

units::Energy Work(units::Force force, units::Length displacement) {
  return units::Energy{force.value * displacement.value};
}

units::Force Friction(units::Quantity<0, 0, 0> friction_coef, units::Force normal_force) {
  return units::Force{friction_coef.value * normal_force.value};
}

units::Force StaticFrictionMax(units::Quantity<0, 0, 0> static_coef, units::Force normal_force) {
  return units::Force{static_coef.value * normal_force.value};
}

}  // namespace physics::mech
