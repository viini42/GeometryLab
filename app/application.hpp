#ifndef DRAWER_APPLICATION_HPP
#define DRAWER_APPLICATION_HPP
#include <memory>

#include "renderer/window.hpp"

class Application
{
public:
  Application();

  void Finish();
  void Run();

private:
  Window m_window;
  Canvas m_canvas;
  Renderer m_renderer;
  Camera m_camera;
};

#endif // DRAWER_APPLICATION_HPP
