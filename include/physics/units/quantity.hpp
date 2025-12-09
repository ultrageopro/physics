#pragma once

#include <cmath>

namespace physics::units {

// Класс представляющий собой величину для дальнейших вычислений
template <int T, int L, int M>
struct Quantity {
  double value;
};

template <typename>
inline constexpr bool kIsQuantityV = false;

template <int T, int L, int M>
inline constexpr bool kIsQuantityV<Quantity<T, L, M>> = true;

template <typename U>
constexpr double ScalarValue(const U& x) {
  if constexpr (std::is_arithmetic_v<U>) {
    return x;
  } else {
    return x.value;
  }
}

// Операторы для вычисления величин
// Определены для двух величин и для величины и числа
// Очень еще удобно что умножение и сложение со скаляром некоммутативно потому что мне лень было определять левый операнд
template <int T, int L, int M>
constexpr Quantity<T, L, M> operator*(const Quantity<T, L, M>& left, double right) {
  return Quantity<T, L, M>{left.value * right};
};

template <int T, int L, int M>
constexpr Quantity<T, L, M> operator/(const Quantity<T, L, M>& left, double right) {
  return Quantity<T, L, M>{left.value / right};
};

template <int Power, int T, int L, int M>
constexpr Quantity<T * Power, L * Power, M * Power> Pow(const Quantity<T, L, M>& left) {
  return Quantity<T * Power, L * Power, M * Power>{std::pow(left.value, Power)};
};

template <int T, int L, int M>
constexpr Quantity<T, L, M> operator+(const Quantity<T, L, M>& left, double right) {
  return Quantity<T, L, M>{left.value + right};
};

template <int T, int L, int M>
constexpr Quantity<T, L, M> operator-(const Quantity<T, L, M>& left, double right) {
  return Quantity<T, L, M>{left.value - right};
};

template <int T, int L, int M>
constexpr Quantity<T, L, M> operator+(const Quantity<T, L, M>& left, const Quantity<T, L, M>& right) {
  return Quantity<T, L, M>{left.value + right.value};
};

template <int T, int L, int M>
constexpr Quantity<T, L, M> operator-(const Quantity<T, L, M>& left, const Quantity<T, L, M>& right) {
  return Quantity<T, L, M>{left.value - right.value};
};

template <int T1, int L1, int M1, int T2, int L2, int M2>
constexpr Quantity<T1 + T2, L1 + L2, M1 + M2> operator*(const Quantity<T1, L1, M1>& left, const Quantity<T2, L2, M2>& right) {
  return Quantity<T1 + T2, L1 + L2, M1 + M2>{left.value * right.value};
};

template <int T1, int L1, int M1, int T2, int L2, int M2>
constexpr Quantity<T1 - T2, L1 - L2, M1 - M2> operator/(const Quantity<T1, L1, M1>& left, const Quantity<T2, L2, M2>& right) {
  return Quantity<T1 - T2, L1 - L2, M1 - M2>{left.value / right.value};
};

// Основные единицы измерения
using Time = Quantity<1, 0, 0>;
using Length = Quantity<0, 1, 0>;
using Weight = Quantity<0, 0, 1>;
using Speed = Quantity<-1, 1, 0>;
using Acceleration = Quantity<-2, 1, 0>;
using Force = Quantity<-2, 1, 1>;
using Energy = Quantity<-2, 2, 1>;
using SpringConstant = Quantity<-2, 1, 1>;

// Удобство для задания переменных суффиксами
constexpr inline Time operator""_s(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Length operator""_m(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Weight operator""_kg(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Speed operator""_ms(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Acceleration operator""_ms2(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Force operator""_N(long double value) {
  return {static_cast<double>(value)};
};
constexpr inline Energy operator""_J(long double value) {
  return {static_cast<double>(value)};
};

}  // namespace physics::units