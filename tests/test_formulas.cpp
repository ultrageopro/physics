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

TEST(VectorTest, ElasticForceCorrect) {
  using pu::operator""_m;
  using pu::operator""_N;

  pu::Quantity<-2, 1, 1> k{100.0};
  auto x = 0.2_m;

  EXPECT_DOUBLE_EQ(pm::ElasticForce(k, x).value, 20.0);
}

TEST(VectorTest, ElasticPotentialEnergyCorrect) {
  using pu::operator""_m;

  pu::Quantity<-2, 1, 1> k{100.0};
  auto x = 0.3_m;

  EXPECT_DOUBLE_EQ(pm::ElasticPotentialEnergy(k, x).value, 4.5);
}