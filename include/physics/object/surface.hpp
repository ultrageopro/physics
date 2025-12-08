#pragma once

#include <physics/units/quantity.hpp>
#include <physics/vector/vector.hpp>

namespace physics::object {

class Surface {
 public:
  units::Quantity<0, 0, 0> mu = {1.0};
  Surface() = default;

  explicit Surface(units::Quantity<0, 0, 0> mu) : mu(mu) {
  }
};

}  // namespace physics::object