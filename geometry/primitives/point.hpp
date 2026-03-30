#ifndef POINT_HPP
#define POINT_HPP

#include "common/number_aliases.hpp"

struct Point
{
  constexpr Point(f64 xx, f64 yy) : x(xx), y(yy) {}

  f64 x;
  f64 y;
};

#endif // POINT_HPP
