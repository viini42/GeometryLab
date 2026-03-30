#include "canvas.hpp"

Canvas::Canvas(u64 width, u64 height) :
    m_limits(0, f64(width), f64(height), 0),
    m_current_scene(std::make_unique<Scene>())
{
  std::vector<PointEnt> points;
  points.emplace_back(Point{ 400, 300 }, Color{ .r = 0.0F, .g = 0.0F, .b = 0.0F });
  m_current_scene->SetPoints(points);
}

const std::vector<PointEnt>& Canvas::GetPoints() const
{
  return m_current_scene->GetPoints();
}

const WorldLimits& Canvas::GetLimits() const
{
  return m_limits;
}

void Canvas::AddPoint(const Point& pt)
{
  m_current_scene->AddPoint(PointEnt{ .position=pt, .color=m_current_color });
}
