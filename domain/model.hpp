#ifndef MODEL_HPP
#define MODEL_HPP

#include "geometry/line.hpp"
#include "geometry/point.hpp"

#include <list>

class Model
{
public:
  Model() : m_points(), m_lines(){}

  [[nodiscard]] const auto& GetPoints() const { return m_points; }
  [[nodiscard]] const auto& GetLines() const { return m_lines; }

  void SetPoints(const std::list<Point>& points) { m_points = points; }

private:
  std::list<Point> m_points;
  std::list<Line> m_lines;
};

#endif // MODEL_HPP
