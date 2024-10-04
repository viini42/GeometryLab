#ifndef POINT_HPP
#define POINT_HPP

#include "number_aliases.hpp"

class Point
{
public:
  constexpr Point(f64 x, f64 y) : m_x(x), m_y(y) {}

  [[nodiscard]] auto X() const { return m_x; }
  [[nodiscard]] auto Y() const { return m_y; }

private:
  f64 m_x;
  f64 m_y;
};

#endif // POINT_HPP
