#pragma once

#include <physics/units/quantity.hpp>
#include <physics/vector/vector.hpp>
#include "physics/object/surface.hpp"

namespace physics::object {

// Объект в пространстве
// По дефолту считаем, что объект находится на поверхности Земли
class Object {
 public:
  units::Weight weight = units::Weight{1.0};
  vector::Vector<units::Length, 3> position{};
  vector::Vector<units::Speed, 3> speed{};
  vector::Vector<units::Acceleration, 3> acceleration{};

  Object() = default;

  explicit Object(units::Weight mass, vector::Vector<units::Length, 3> position = {}, vector::Vector<units::Speed, 3> speed = {},
                  vector::Vector<units::Acceleration, 3> acceleration = vector::Vector<units::Acceleration, 3>{})
      : weight(mass), position(position), speed(speed), acceleration(acceleration) {
  }

  // Сила тяготения к поверхности (Масса)
  vector::Vector<units::Force, 3> Mass() const;

  // Трение
  vector::Vector<units::Force, 3> FrictionForce(const Surface& surface) const;

  // Расстояние
  units::Length DistanceTo(const Object& other) const;
  vector::Vector<units::Quantity<0, 0, 0>, 3> DirectionTo(const Object& other) const;

  // Гравитационная сила
  units::Force GravitationalForceMagnitude(const Object& other) const;
  vector::Vector<units::Force, 3> GravitationalForceVector(const Object& other) const;

  // Для симуляции
  void ApplyForce(const vector::Vector<units::Force, 3>& force);
  void Update(units::Time dt);
};

}  // namespace physics::object