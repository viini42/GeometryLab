#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "../../common/number_aliases.hpp"
#include "point.hpp"

struct Segment
{
  Segment(const Point& pp1, const Point& pp2);

  Point p1;
  Point p2;
};

#endif
