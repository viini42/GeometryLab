#ifndef DRAWER_CANVAS_HPP
#define DRAWER_CANVAS_HPP

#include "../common/number_aliases.hpp"
#include "scene.hpp"
#include "world_limits.hpp"

#include <memory>
#include <vector>

class Canvas
{
public:
  Canvas(u64 width, u64 height);

  [[nodiscard]] const std::vector<PointEnt>& GetPoints() const;
  [[nodiscard]] const WorldLimits& GetLimits() const;
  void AddPoint(const Point& pt);

private:
  WorldLimits m_limits;
  std::unique_ptr<Scene> m_current_scene;
  Color m_current_color;
};

#endif // DRAWER_CANVAS_HPP
