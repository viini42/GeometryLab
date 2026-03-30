#ifndef GEOMETRYLAB_RENDERER_HPP
#define GEOMETRYLAB_RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

struct WorldLimits;
struct PointEnt;
class Camera;
class Canvas;
class Renderer
{
public:
  explicit Renderer(sf::RenderWindow& renderWindow);

  void Draw(const Canvas& canvas, const Camera& camera);

  void Clear();

  void Display();

private:
  void DrawPoint(const PointEnt& pt, const Camera& camera, const WorldLimits& limits);

  sf::RenderWindow& m_render;
};

#endif // GEOMETRYLAB_RENDERER_HPP
