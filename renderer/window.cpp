#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <print>

Window::Window(u32 width, u32 height, const std::string& title) :
    m_window(sf::VideoMode({ width, height }), title)
{
  m_window.setFramerateLimit(60);
}

bool Window::IsOpen()
{
  // OnEvent(m_window.pollEvent());

  // m_renderer.Clear();
  // renderer.render(m_canvas);
  // m_renderer.Draw(m_canvas, m_camera, m_window);
  // ObjectDrawer::Draw(m_canvas, m_window, m_world);
  // m_window.display();

  // std::println("x={}, y={}", sf::Mouse::getPosition(m_window).x, int(m_window.getSize().y) -
  // sf::Mouse::getPosition(m_window).y);

  return m_window.isOpen();
}

sf::RenderWindow& Window::GetRenderWindow()
{
  return m_window;
}

bool Window::HandleEvents()
{
  auto ev = m_window.pollEvent();
  if (!ev)
  {
    return false;
  }

  if (ev->is<sf::Event::Closed>() && m_on_close)
  {
    m_on_close();
    return true;
  }

  if (ev->is<sf::Event::MouseButtonPressed>() && m_on_mouse_button_clicked)
  {
    const auto& data = ev->getIf<sf::Event::MouseButtonPressed>();
    auto button = static_cast<MouseButton>(static_cast<i32>(data->button));
    const f64 x = static_cast<MouseButton>(static_cast<i32>(data->position.x));
    const f64 y = static_cast<MouseButton>(static_cast<i32>(data->position.y));
    m_on_mouse_button_clicked(button, { x, y });
    return true;
  }

  return true;
}

void Window::Close()
{
  m_window.close();
}

void Window::SetOnCloseEvent(const std::function<void()>& callback)
{
  m_on_close = callback;
}

void Window::SetOnMouseButtonPressedEvent(const std::function<void(MouseButton, Point)>& callback)
{
  m_on_mouse_button_clicked = callback;
}