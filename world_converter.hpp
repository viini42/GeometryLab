#ifndef WORLD_HPP
#define WORLD_HPP

#include "number_aliases.hpp"
#include "point.hpp"

#include <SFML/System/Vector2.hpp>

struct Limits
{
  f64 start;
  f64 end;
  f64 top;
  f64 bot;
};

class World
{
public:
  World(u32 windowWidth, u32 windowHeight);

  [[nodiscard]] const Limits& GetLimits() const;

  [[nodiscard]] sf::Vector2<f64> ConvertToWorld(i32 screenX, i32 screenY) const;

  [[nodiscard]] sf::Vector2f ConvertToScreen(const Point& worldPt) const;

  void MoveHorizontally(f64 value);

  void MoveVertically(f64 value);

  void ZoomOut();

  void ZoomIn();

private:
  u32 m_window_width;
  u32 m_window_height;
  Limits m_limits;
};

#endif // WORLD_HPP
