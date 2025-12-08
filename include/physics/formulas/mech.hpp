#pragma once

#include <physics/units/quantity.hpp>

namespace physics::mech {

units::Energy KineticEnergy(units::Mass mass, units::Speed speed);

units::Energy PotentialEnergy(units::Mass mass, units::Acceleration g, units::Length height);

units::Force NewtonSecondLaw(units::Mass mass, units::Acceleration accel);

units::Speed AverageSpeed(units::Length distance, units::Time time);

units::Length UniformMotion(units::Length initial, units::Speed speed, units::Time time);

units::Length AcceleratedMotion(units::Length initial, units::Speed v0, units::Acceleration a, units::Time t);

units::Quantity<0, 1, 1> Momentum(units::Mass mass, units::Speed speed);

units::Energy Work(units::Force force, units::Length displacement);

units::Force Friction(units::Quantity<0, 0, 0> friction_coef, units::Force normal_force);

units::Force StaticFrictionMax(units::Quantity<0, 0, 0> static_coef, units::Force normal_force);

}  // namespace physics::mech