#pragma once

#include <array>
#include <cstddef>

#include <physics/units/quantity.hpp>

namespace physics::vector {

// Стандартный вектор размера N
template <typename T, std::size_t N>
class Vector {
  static_assert(std::is_arithmetic_v<T> || physics::units::kIsQuantityV<T>, "Vector<T,N>: T must be arithmetic or a Quantity type");

 public:
  std::array<T, N> data;

  constexpr T& operator[](std::size_t i) {
    return data[i];
  }
  constexpr const T& operator[](std::size_t i) const {
    return data[i];
  }

  T& First() {
    return data[0];
  }
  const T& First() const {
    return data[0];
  }

  T& Last() {
    return data[N - 1];
  }
  const T& Last() const {
    return data[N - 1];
  }

  constexpr std::size_t Size() const {
    return N;
  }

  constexpr void Fill(const T& value) {
    for (std::size_t i = 0; i < N; ++i) {
      data[i] = value;
    }
  }

  constexpr bool operator==(const Vector& other) const {
    for (std::size_t i = 0; i < N; ++i) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  constexpr Vector operator+(const Vector& other) const {
    Vector<T, N> result{};
    for (std::size_t i = 0; i < N; ++i) {
      result[i] = data[i] + other[i];
    }
    return result;
  }

  constexpr Vector operator-(const Vector& other) const {
    Vector<T, N> result{};
    for (std::size_t i = 0; i < N; ++i) {
      result[i] = data[i] - other[i];
    }
    return result;
  }

  constexpr Vector operator*(double other) const {
    Vector<T, N> result{};
    for (std::size_t i = 0; i < N; ++i) {
      result[i] = data[i] * other;
    }
    return result;
  }

  constexpr Vector operator/(double other) const {
    Vector<T, N> result{};
    for (std::size_t i = 0; i < N; ++i) {
      result[i] = data[i] / other;
    }
    return result;
  }
};

template <typename T1, typename T2, std::size_t N>
constexpr auto Dot(const Vector<T1, N>& left, const Vector<T2, N>& right) {
  using MulType = decltype(left[0] * right[0]);
  MulType sum{0.0};

  for (std::size_t i = 0; i < N; ++i) {
    sum = sum + (left[i] * right[i]);
  }
  return sum;
}

template <typename T, std::size_t N>
constexpr T Norm(const Vector<T, N>& v) {
  auto dt = Dot(v, v);
  return T{std::sqrt(units::ScalarValue(dt))};
}

template <typename T, std::size_t N>
constexpr Vector<units::Quantity<0, 0, 0>, N> Normalize(const Vector<T, N>& v) {
  using Dimensionless = units::Quantity<0, 0, 0>;

  Vector<Dimensionless, N> result{};

  T norm = Norm(v);
  double len = units::ScalarValue(norm);

  for (std::size_t i = 0; i < N; ++i) {
    result[i] = len != 0 ? Dimensionless{units::ScalarValue(v[i]) / len} : Dimensionless{0};
  }

  return result;
}

}  // namespace physics::vector