#ifndef LINE_HPP
#define LINE_HPP
#include "point.hpp"

class Line
{
public:
  Line(const Point& p1, const Point& p2);

  [[nodiscard]] const auto& P1() const { return m_p1; }
  [[nodiscard]] const auto& P2() const { return m_p2; }

private:
  Point m_p1;
  Point m_p2;
};

#endif // LINE_HPP
