#pragma once

#include <physics/units/quantity.hpp>

namespace physics::gravity {

units::Force GravitationalForce(units::Weight m1, units::Weight m2, units::Length distance);

units::Acceleration GravitationalAcceleration(units::Weight mass, units::Length radius);

units::Energy GravitationalPotentialEnergy(units::Weight m1, units::Weight m2, units::Length distance);

units::Speed EscapeVelocity(units::Weight planet, units::Length radius);

units::Speed OrbitalVelocity(units::Weight planet, units::Length radius);

}  // namespace physics::gravity