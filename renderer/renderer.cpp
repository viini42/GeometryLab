#include "renderer.hpp"

#include "camera.hpp"
#include "model/canvas.hpp"
#include "model/entities/pointer_ent.hpp"
#include "model/world_limits.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <algorithm>

Renderer::Renderer(sf::RenderWindow& renderWindow) : m_render(renderWindow) {}

void Renderer::Draw(const Canvas& canvas, const Camera& camera)
{
  const auto& limits = canvas.GetLimits();
  const auto& points = canvas.GetPoints();
  std::ranges::for_each(points, [&](const auto& p) { DrawPoint(p, camera, limits); });
}

void Renderer::Clear()
{
  m_render.clear();
}

void Renderer::Display()
{
  m_render.display();
}

void Renderer::DrawPoint(const PointEnt& pt, const Camera& camera, const WorldLimits& limits)
{
  auto [screen_x, screen_y] = camera.ConvertToScreen(pt.position, limits);
  constexpr auto radius = 2.0;
  sf::CircleShape circle{ radius };
  circle.setPosition(
    { static_cast<float>(screen_x - radius), static_cast<float>(screen_y - radius) });
  m_render.draw(circle);
}
