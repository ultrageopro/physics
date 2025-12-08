#pragma once

#include <physics/units/quantity.hpp>

namespace physics::gravity {

units::Force GravitationalForce(units::Mass m1, units::Mass m2, units::Length distance);

units::Acceleration GravitationalAcceleration(units::Mass mass, units::Length radius);

units::Energy GravitationalPotentialEnergy(units::Mass m1, units::Mass m2, units::Length distance);

units::Speed EscapeVelocity(units::Mass planet, units::Length radius);

units::Speed OrbitalVelocity(units::Mass planet, units::Length radius);

}  // namespace physics::gravity