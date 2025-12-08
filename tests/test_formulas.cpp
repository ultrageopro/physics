#include <gtest/gtest.h>
#include <physics/formulas/mech.hpp>
#include <physics/units/quantity.hpp>

namespace pm = physics::mech;
namespace pu = physics::units;

TEST(VectorTest, KineticEnergyCorrect) {
  using pu::operator""_kg;
  using pu::operator""_ms;

  auto speed = 10.0_ms;
  auto mass = 1.0_kg;

  EXPECT_DOUBLE_EQ(pm::KineticEnergy(mass, speed).value, 50.0);
}
