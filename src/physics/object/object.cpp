#include <cmath>

#include <cstdlib>
#include <physics/object/object.hpp>
#include <physics/formulas/gravity.hpp>
#include <physics/formulas/mech.hpp>
#include <physics/vector/vector.hpp>
#include "physics/constants.hpp"
#include "physics/units/quantity.hpp"

namespace physics::object {

vector::Vector<units::Force, 3> Object::Mass() const {
  double g = constants::kEarthGravity.value;
  double a_z = acceleration[2].value;
  double effective = g - a_z;

  if (effective <= 0.0) {
    return {units::Force{0}, units::Force{0}, units::Force{0}};
  }

  units::Force n{mass.value * effective};
  return {units::Force{0}, units::Force{0}, n};
}

vector::Vector<units::Force, 3> Object::FrictionForce(const Surface& surface) const {
  vector::Vector<units::Speed, 3> horizontal_speed{speed[0], speed[1], units::Speed{0}};
  units::Speed v = vector::Norm(horizontal_speed);

  if (units::ScalarValue(v) == 0.0) {
    return vector::Vector<units::Force, 3>{units::Force{0}, units::Force{0}, units::Force{0}};
  }

  vector::Vector<units::Force, 3> nvec = Mass();
  units::Force n = nvec[2];

  if (units::ScalarValue(n) <= 0.0) {
    return {units::Force{0}, units::Force{0}, units::Force{0}};
  }

  units::Force ff = physics::mech::StaticFrictionMax(surface.mu, n);
  vector::Vector<units::Quantity<0, 0, 0>, 3> dir = vector::Normalize(horizontal_speed);

  return vector::Vector<units::Force, 3>{units::Force{-units::ScalarValue(ff) * units::ScalarValue(dir[0])},
                                         units::Force{-units::ScalarValue(ff) * units::ScalarValue(dir[1])}, units::Force{0}};
}

units::Length Object::DistanceTo(const Object& other) const {
  auto diff = other.position - position;
  auto squared = vector::Dot(diff, diff);
  return units::Length{std::sqrt(units::ScalarValue(squared))};
}

vector::Vector<units::Quantity<0, 0, 0>, 3> Object::DirectionTo(const Object& other) const {
  auto diff = other.position - position;
  return vector::Normalize(diff);
}

units::Force Object::GravitationalForceMagnitude(const Object& other) const {
  return gravity::GravitationalForce(mass, other.mass, DistanceTo(other));
}

vector::Vector<units::Force, 3> Object::GravitationalForceVector(const Object& other) const {
  auto force = GravitationalForceMagnitude(other);
  auto dir = DirectionTo(other);

  vector::Vector<units::Force, 3> result{};
  for (std::size_t i = 0; i < 3; ++i) {
    double unit = units::ScalarValue(dir[i]);
    result[i] = units::Force{force.value * unit};
  }

  return result;
}

void Object::ApplyForce(const vector::Vector<units::Force, 3>& force) {
  for (std::size_t i = 0; i < 3; ++i) {
    acceleration[i] = acceleration[i] + units::Acceleration{force[i].value / mass.value};
  }
}

void Object::Update(units::Time dt) {
  for (std::size_t i = 0; i < 3; ++i) {
    speed[i] = speed[i] + units::Speed{acceleration[i].value * dt.value};
    position[i] = position[i] + units::Length{speed[i].value * dt.value};
  }
}

}  // namespace physics::object