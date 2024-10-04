#ifndef OBJECT_DRAWER_HPP
#define OBJECT_DRAWER_HPP
#include "line.hpp"
#include "point.hpp"
#include "world_converter.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

class ObjectDrawer
{
public:
  // TODO: abstract renderer to work with world coordinates
  static void DrawPoint(sf::RenderTarget& renderer, const World& world, const Point& pt);

  static void DrawLine(sf::RenderTarget& renderer, const World& world, const Line& line);
};

#endif // OBJECT_DRAWER_HPP
