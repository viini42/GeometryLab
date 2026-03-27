#include "window.hpp"

#include <SFML/Graphics/Font.hpp>

Window::Window(u32 width, u32 height, const std::string& title) :
    m_window(sf::VideoMode({ width, height }), title), m_canvas(width, height)
{
  m_window.setFramerateLimit(60);
}