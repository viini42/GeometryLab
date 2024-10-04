#include "object_drawer.hpp"

#include "world_converter.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

void ObjectDrawer::DrawPoint(sf::RenderTarget& renderer, const World& world, const Point& pt)
{
  auto [screen_x, screen_y] = world.ConvertToScreen(pt);
  sf::CircleShape circle{ 2.0f, 4 };
  circle.setPosition(screen_x, screen_y);
  renderer.draw(circle);
}

void ObjectDrawer::DrawLine(sf::RenderTarget& renderer, const World& world, const Line& line)
{
  auto [p1x, p1y] = world.ConvertToScreen(line.P1());
  auto [p2x, p2y] = world.ConvertToScreen(line.P2());
  sf::Vertex verts[] = { sf::Vertex{ { p1x, p1y }, sf::Color::White },
                         sf::Vertex{ { p2x, p2y }, sf::Color::White } };
  renderer.draw(verts, 2, sf::Lines);
}