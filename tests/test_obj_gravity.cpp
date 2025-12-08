#include <gtest/gtest.h>

#include <physics/object/object.hpp>
#include <physics/constants.hpp>
#include <physics/units/quantity.hpp>
#include <physics/vector/vector.hpp>

namespace po = physics::object;
namespace pu = physics::units;
namespace pv = physics::vector;
namespace pc = physics::constants;

TEST(ObjectGravityTest, DistanceCorrect) {
  po::Object a(pu::Mass{10.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}});
  po::Object b(pu::Mass{20.0}, pv::Vector<pu::Length, 3>{{pu::Length{3.0}, pu::Length{4.0}, pu::Length{0}}});

  pu::Length dist = a.DistanceTo(b);

  EXPECT_DOUBLE_EQ(dist.value, 5.0);
}

TEST(ObjectGravityTest, DirectionCorrect) {
  po::Object a(pu::Mass{10.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}});
  po::Object b(pu::Mass{20.0}, pv::Vector<pu::Length, 3>{{pu::Length{3.0}, pu::Length{4.0}, pu::Length{0}}});

  auto dir = a.DirectionTo(b);

  EXPECT_NEAR(dir[0].value, 0.6, 1e-9);
  EXPECT_NEAR(dir[1].value, 0.8, 1e-9);
  EXPECT_DOUBLE_EQ(dir[2].value, 0.0);
}

TEST(ObjectGravityTest, GravitationalForceMagnitudeCorrect) {
  po::Object a(pu::Mass{10.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}});
  po::Object b(pu::Mass{20.0}, pv::Vector<pu::Length, 3>{{pu::Length{2.0}, pu::Length{0}, pu::Length{0}}});

  pu::Force force = a.GravitationalForceMagnitude(b);

  double expected = pc::kG.value * 10.0 * 20.0 / (2 * 2);

  EXPECT_NEAR(force.value, expected, 1e-15);
}

TEST(ObjectGravityTest, GravitationalForceVectorCorrect) {
  po::Object a(pu::Mass{10.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}});
  po::Object b(pu::Mass{20.0}, pv::Vector<pu::Length, 3>{{pu::Length{2.0}, pu::Length{0}, pu::Length{0}}});

  auto fvec = a.GravitationalForceVector(b);

  const double expected_mag = pc::kG.value * 10.0 * 20.0 / 4.0;

  EXPECT_NEAR(fvec[0].value, expected_mag, 1e-15);
  EXPECT_DOUBLE_EQ(fvec[1].value, 0.0);
  EXPECT_DOUBLE_EQ(fvec[2].value, 0.0);
}