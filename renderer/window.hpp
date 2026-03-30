#ifndef DRAWER_WINDOW_HPP
#define DRAWER_WINDOW_HPP

#include "MouseButton.hpp"
#include "camera.hpp"
#include "common/aliases.hpp"
#include "common/number_aliases.hpp"
#include "model/canvas.hpp"
#include "renderer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

class Window
{
public:
  Window(u32 width, u32 height, const std::string& title);

  bool IsOpen();

  sf::RenderWindow& GetRenderWindow();

  [[nodiscard]] bool HandleEvents();

  void Close();

  void SetOnCloseEvent(const std::function<void()>& callback);
  void SetOnMouseButtonPressedEvent(const std::function<void(MouseButton, Point)>& callback);

private:
  sf::RenderWindow m_window;

  std::function<void()> m_on_close;
  std::function<void(MouseButton, Point)> m_on_mouse_button_clicked;
};

#endif // DRAWER_WINDOW_HPP
