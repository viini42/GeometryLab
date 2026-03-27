#ifndef DRAWER_WINDOW_HPP
#define DRAWER_WINDOW_HPP

#include "canvas.hpp"
#include "domain/math/number_aliases.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
public:
  Window(u32 width, u32 height, const std::string& title);

private:
  sf::RenderWindow m_window;

  Canvas m_canvas;
};

#endif // DRAWER_WINDOW_HPP
