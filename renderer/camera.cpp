#include "camera.hpp"

#include "model/world_limits.hpp"

Camera::Camera(u32 windowWidth, u32 windowHeight) :
    m_window_width(windowWidth), m_window_height(windowHeight)
{
}

Point Camera::ConvertToScreen(const Point& worldPt, const WorldLimits& limits) const
{
  const auto horizontal_len = worldPt.x - limits.start;
  const auto vertical_len = worldPt.y - limits.bot;
  const auto world_width = limits.end - limits.start;
  const auto world_height = limits.top - limits.bot;
  const auto screen_x = static_cast<f32>(m_window_width * (horizontal_len / world_width));
  const auto screen_y =
    static_cast<f32>(m_window_height * (world_height - vertical_len) / world_height);
  return { screen_x, screen_y };
}

Point Camera::ConvertToWorld(const Point& screenPt, const WorldLimits& limits) const
{
  f64 norm_x = (f64)screenPt.x / m_window_width;
  f64 norm_y = (f64)screenPt.y / m_window_height;
  f64 w_x = norm_x * (limits.end - limits.start) + limits.start;
  f64 w_y = (1.0 - norm_y) * (limits.top - limits.bot) + limits.bot;
  return { w_x, w_y };
}
