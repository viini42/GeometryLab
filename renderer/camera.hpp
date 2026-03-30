#ifndef GEOMETRYLAB_CAMERA_HPP
#define GEOMETRYLAB_CAMERA_HPP
#include "common/number_aliases.hpp"
#include "geometry/primitives/point.hpp"

struct WorldLimits;
class Camera
{
public:
  Camera(u32 windowWidth, u32 windowHeight);

  [[nodiscard]] Point ConvertToScreen(const Point& worldPt, const WorldLimits& limits) const;

  [[nodiscard]] Point ConvertToWorld(const Point& screenPt, const WorldLimits& limits) const;

private:
  u32 m_window_width;
  u32 m_window_height;
};

#endif // GEOMETRYLAB_CAMERA_HPP
