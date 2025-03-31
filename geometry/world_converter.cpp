#include "world_converter.hpp"

World::World(u32 windowWidth, u32 windowHeight) :
    m_window_width(windowWidth),
    m_window_height(windowHeight),
    m_limits({ .start = 0.0,
               .end = 1.0,
               .top = static_cast<f64>(m_window_height) / static_cast<f64>(m_window_width),
               .bot = 0.0 })
{
}

const Limits& World::GetLimits() const
{
  return m_limits;
}

sf::Vector2f World::ConvertToScreen(const Point& worldPt) const
{
  const auto horizontal_len = worldPt.X() - m_limits.start;
  const auto vertical_len = worldPt.Y() - m_limits.bot;
  const auto world_width = m_limits.end - m_limits.start;
  const auto world_height = m_limits.top - m_limits.bot;
  const auto screen_x = static_cast<f32>(m_window_width * (horizontal_len / world_width));
  const auto screen_y =
    static_cast<f32>(m_window_height * (world_height - vertical_len) / world_height);
  return { screen_x, screen_y };
}

void World::MoveHorizontally(const f64 value)
{
  m_limits.start += value;
  m_limits.end += value;
}

void World::MoveVertically(const f64 value)
{
  m_limits.top += value;
  m_limits.bot += value;
}

void World::ZoomOut()
{
  m_limits.start += -0.01;
  m_limits.end += +0.01;
  m_limits.bot += -0.01;
  m_limits.top += +0.01;
}

void World::ZoomIn()
{
  m_limits.start -= -0.01;
  m_limits.end -= +0.01;
  m_limits.bot -= -0.01;
  m_limits.top -= +0.01;
}

sf::Vector2<f64> World::ConvertToWorld(i32 screenX, i32 screenY) const
{
  f64 norm_x = (f64)screenX / m_window_width;
  f64 norm_y = (f64)screenY / m_window_height;

  f64 w_x = norm_x * (m_limits.end - m_limits.start) + m_limits.start;
  f64 w_y = (1.0 - norm_y) * (m_limits.top - m_limits.bot) + m_limits.bot;

  return { w_x, w_y };
}