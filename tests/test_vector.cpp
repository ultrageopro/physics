#include <gtest/gtest.h>
#include <physics/vector/vector.hpp>
#include <physics/units/quantity.hpp>

namespace pv = physics::vector;
namespace pu = physics::units;

TEST(VectorTest, DotProductCorrect) {
  pv::Vector<double, 2> a{{1.0, 2.0}};
  pv::Vector<double, 2> b{{3.0, 4.0}};

  EXPECT_DOUBLE_EQ(pv::Dot(a, b), 11.0);
}

TEST(VectorTest, DotWithLengthUnits) {
  using pu::Length;
  using pu::operator""_m;

  pv::Vector<Length, 2> a{{1.0_m, 2.0_m}};
  pv::Vector<Length, 2> b{{3.0_m, 4.0_m}};

  auto result = pv::Dot(a, b);

  EXPECT_DOUBLE_EQ(result.value, 11.0);
  EXPECT_TRUE((std::is_same_v<decltype(result), pu::Quantity<0, 2, 0>>));
}