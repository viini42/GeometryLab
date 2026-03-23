#ifndef OBJECT_DRAWER_HPP
#define OBJECT_DRAWER_HPP
#include "domain/geometry/line.hpp"
#include "domain/geometry/point.hpp"
#include "domain/geometry/world_converter.hpp"
#include "utils/aliases.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

class Model;

class ObjectDrawer
{
public:
  // TODO: abstract renderer to work with world coordinates
  static void DrawPoint(sf::RenderTarget& renderer, const World& world, const Point& pt);

  static void DrawLine(sf::RenderTarget& renderer, const World& world, const Line& line);

  static void DrawModel(sf::RenderTarget& renderer, const World& world, const Ptr<Model>& model);
};

#endif // OBJECT_DRAWER_HPP
