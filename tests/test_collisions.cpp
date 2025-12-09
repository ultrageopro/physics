#include <gtest/gtest.h>
#include <physics/simulator/simulator.hpp>
#include <physics/object/object.hpp>
#include <physics/vector/vector.hpp>
#include <physics/units/quantity.hpp>

namespace pu = physics::units;
using physics::object::Object;
using physics::simulator::Simulator;
using physics::vector::Vector;

double KE(const Object& o) {
  auto v = o.speed;
  double v2 = v[0].value * v[0].value + v[1].value * v[1].value + v[2].value * v[2].value;

  return 0.5 * o.weight.value * v2;
}

Vector<pu::Speed, 3> Vel(const Object& o) {
  return o.speed;
}

TEST(CollisionTest, HeadOnEqualMassesSwapVelocities) {
  using pu::operator""_kg;
  using pu::operator""_ms;
  using pu::operator""_m;

  Object a(1.0_kg, {0.0_m, 0.0_m, 0.0_m}, {1.0_ms, 0.0_ms, 0.0_ms});

  Object b(1.0_kg, {1.0_m, 0.0_m, 0.0_m}, {1.0_ms * -1, 0.0_ms, 0.0_ms});

  Simulator sim(pu::Length(1.0));
  sim.Objects().push_back(a);
  sim.Objects().push_back(b);

  sim.HandleElasticCollision(sim.Objects()[0], sim.Objects()[1]);

  auto v1 = Vel(sim.Objects()[0]);
  auto v2 = Vel(sim.Objects()[1]);

  EXPECT_NEAR(v1[0].value, -1.0, 1e-12);
  EXPECT_NEAR(v2[0].value, 1.0, 1e-12);
}

TEST(CollisionTest, MomentumConserved) {
  using pu::operator""_kg;
  using pu::operator""_ms;
  using pu::operator""_m;

  Object a(2.0_kg, {0.0_m, 0.0_m, 0.0_m}, {3.0_ms, 0.0_ms, 0.0_ms});
  Object b(1.0_kg, {1.0_m, 0.0_m, 0.0_m}, {0.0_ms, 0.0_ms, 0.0_ms});

  Simulator sim(pu::Length(1.0));
  sim.Objects().push_back(a);
  sim.Objects().push_back(b);

  double p_before = 2.0 * 3.0 + 1.0 * 0.0;

  sim.HandleElasticCollision(sim.Objects()[0], sim.Objects()[1]);

  auto v1 = sim.Objects()[0].speed[0].value;
  auto v2 = sim.Objects()[1].speed[0].value;

  double p_after = 2.0 * v1 + 1.0 * v2;

  EXPECT_NEAR(p_before, p_after, 1e-12);
}

TEST(CollisionTest, KineticEnergyConserved) {
  using pu::operator""_kg;
  using pu::operator""_ms;
  using pu::operator""_m;

  Object a(2.0_kg, {0.0_m, 0.0_m, 0.0_m}, {3.0_ms, 0.0_ms, 0.0_ms});
  Object b(1.0_kg, {1.0_m, 0.0_m, 0.0_m}, {1.0_ms * -1, 0.0_ms, 0.0_ms});

  Simulator sim(pu::Length(1.0));
  sim.Objects().push_back(a);
  sim.Objects().push_back(b);

  double e_before = KE(sim.Objects()[0]) + KE(sim.Objects()[1]);

  sim.HandleElasticCollision(sim.Objects()[0], sim.Objects()[1]);

  double e_after = KE(sim.Objects()[0]) + KE(sim.Objects()[1]);

  EXPECT_NEAR(e_before, e_after, 1e-12);
}

TEST(CollisionTest, TangentialComponentUnchanged) {
  using pu::operator""_kg;
  using pu::operator""_ms;
  using pu::operator""_m;

  physics::object::Object a(1.0_kg, {0.0, 0.0, 0.0}, {1.0_ms, 1.0_ms, 0.0_ms});
  physics::object::Object b(1.0_kg, {1.0, 0.0, 0.0}, {0.0_ms, 0.0_ms, 0.0_ms});
  physics::simulator::Simulator sim(0.1_m);

  sim.Objects().push_back(a);
  sim.Objects().push_back(b);

  auto& A = sim.Objects()[0];
  auto& B = sim.Objects()[1];

  auto delta = B.position - A.position;
  double dist = physics::vector::Norm(delta).value;
  auto n = physics::vector::Normalize(delta);

  physics::vector::Vector<physics::units::Speed, 3> t{};
  t[0] = {-n[1].value};
  t[1] = {n[0].value};
  t[2] = {0.0};

  double tnorm = std::sqrt(t[0].value * t[0].value + t[1].value * t[1].value);
  t[0].value /= tnorm;
  t[1].value /= tnorm;

  double t_before = physics::vector::Dot(A.speed, t).value;
  sim.HandleCollisions();
  double t_after = physics::vector::Dot(A.speed, t).value;

  EXPECT_NEAR(t_before, t_after, 1e-12);
}