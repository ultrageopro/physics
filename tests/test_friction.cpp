#include <gtest/gtest.h>
#include <physics/object/object.hpp>
#include <physics/object/surface.hpp>
#include <physics/constants.hpp>
#include <physics/vector/vector.hpp>
#include <physics/units/quantity.hpp>

namespace po = physics::object;
namespace pu = physics::units;
namespace pv = physics::vector;
namespace pc = physics::constants;

TEST(SurfaceTest, MassBasicStandingObject) {
  using pu::operator""_m;
  using pu::operator""_ms;

  po::Object obj(pu::Mass{5.0}, pv::Vector<pu::Length, 3>{{0.0_m, 0.0_m, 0.0_m}}, pv::Vector<pu::Speed, 3>{{0.0_ms, 0.0_ms, 0.0_ms}},
                 pv::Vector<pu::Acceleration, 3>{{0, 0, 0}});

  auto normal = obj.Mass();
  double expected_n = 5.0 * pc::kEarthGravity.value;

  EXPECT_DOUBLE_EQ(normal[2].value, expected_n);
}

TEST(FrictionTest, NoHorizontalMotionMeansNoFriction) {
  po::Surface surf(pu::Quantity<0, 0, 0>{0.5});

  po::Object obj(pu::Mass{5.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}},
                 pv::Vector<pu::Speed, 3>{{pu::Speed{0}, pu::Speed{0}, pu::Speed{0}}},
                 pv::Vector<pu::Acceleration, 3>{{pu::Acceleration{0}, pu::Acceleration{0}, pc::kEarthGravity * -1}});

  auto friction = obj.FrictionForce(surf);

  EXPECT_DOUBLE_EQ(friction[0].value, 0.0);
  EXPECT_DOUBLE_EQ(friction[1].value, 0.0);
  EXPECT_DOUBLE_EQ(friction[2].value, 0.0);
}

TEST(FrictionTest, HorizontalMotionCreatesFrictionOppositeDirection) {
  using pu::operator""_m;
  using pu::operator""_ms;

  po::Surface surf(pu::Quantity<0, 0, 0>{0.5});
  po::Object obj(pu::Mass{5.0}, pv::Vector<pu::Length, 3>{{0.0_m, 0.0_m, 0.0_m}}, pv::Vector<pu::Speed, 3>{{3.0_ms, 4.0_ms, 0.0_ms}},
                 pv::Vector<pu::Acceleration, 3>{{0, 0, 0}});

  auto friction = obj.FrictionForce(surf);

  const double n = 5.0 * pc::kEarthGravity.value;
  const double ff = 0.5 * n;

  const double expected_fx = -ff * (3.0 / 5.0);
  const double expected_fy = -ff * (4.0 / 5.0);

  EXPECT_NEAR(friction[0].value, expected_fx, 1e-6);
  EXPECT_NEAR(friction[1].value, expected_fy, 1e-6);
  EXPECT_DOUBLE_EQ(friction[2].value, 0.0);
}

TEST(SurfaceTest, MassZeroIfAccelerationIsUpwards) {
  po::Object obj(pu::Mass{1.0}, pv::Vector<pu::Length, 3>{{pu::Length{0}, pu::Length{0}, pu::Length{0}}},
                 pv::Vector<pu::Speed, 3>{{pu::Speed{0}, pu::Speed{0}, pu::Speed{0}}},
                 pv::Vector<pu::Acceleration, 3>{{pu::Acceleration{0}, pu::Acceleration{0}, pu::Acceleration{pc::kEarthGravity}}});

  auto normal = obj.Mass();

  EXPECT_DOUBLE_EQ(normal[0].value, 0.0);
  EXPECT_DOUBLE_EQ(normal[1].value, 0.0);
  EXPECT_DOUBLE_EQ(normal[2].value, 0.0);
}