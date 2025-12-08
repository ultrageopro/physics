#pragma once

#include <physics/units/quantity.hpp>

namespace physics::constants {

inline constexpr units::Quantity<-2, 3, -1> kG{6.67430e-11};
inline constexpr units::Acceleration kEarthGravity{9.80665};

}  // namespace physics::constants