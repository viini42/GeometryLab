#include "application.hpp"

#include <print>

namespace
{
  constexpr auto WIDTH = 800;
  constexpr auto HEIGHT = 600;
}

Application::Application() :
    m_window(WIDTH, HEIGHT, "Application"),
    m_canvas(WIDTH, HEIGHT),
    m_renderer(m_window.GetRenderWindow()),
    m_camera(WIDTH, HEIGHT)
{
  m_window.SetOnCloseEvent([&]() { m_window.Close(); });
  m_window.SetOnMouseButtonPressedEvent(
    [&](MouseButton bt, Point pt)
    {
      std::println("{},{},{}", i32(bt), pt.x, pt.y);
      m_canvas.AddPoint(m_camera.ConvertToWorld(pt, m_canvas.GetLimits()));
    });
}

void Application::Finish()
{
  std::println("Finishing...");
}

void Application::Run()
{
  while (m_window.IsOpen())
  {
    m_renderer.Clear();

    while (m_window.HandleEvents())
    {
    }

    m_renderer.Draw(m_canvas, m_camera);
    m_renderer.Display();
  }

  Finish();
}