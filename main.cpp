#include "object_drawer.hpp"
#include "world_converter.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <format>

std::vector<Point> circles{};
Line l_x{ Point{ 0, -1000 }, Point{ 0, 1000 } };
Line l_y{ Point{ -1000, 0 }, Point{ 1000, 0 } };

int main()
{
  // Create a window with the resolution of 800x600
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

  // Set the frame rate limit to 60 FPS
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("fonts/Inter-Regular.ttf"))
  {
    return -1;
  }
  sf::Text text_coords;
  text_coords.setFont(font);
  text_coords.setCharacterSize(12);
  text_coords.setFillColor(sf::Color::White);
  sf::Text text_zoom = text_coords;

  World world{ window.getSize().x, window.getSize().y };
  world.MoveVertically(-0.1);
  world.MoveHorizontally(-0.1);

  // auto y_axis_bot = world.ConvertToScreen(0, -1);
  // auto y_axis_top = world.ConvertToScreen(0, +1);
  // auto x_axis_start = world.ConvertToScreen(-1, 0);
  // auto x_axis_end = world.ConvertToScreen(+1, 0);
  // sf::Vertex y_axis[]{
  //   sf::Vertex(sf::Vector2f{ static_cast<float>(y_axis_bot.x), static_cast<float>(y_axis_bot.y)
  //   },
  //              sf::Color::Red),
  //   sf::Vertex(sf::Vector2f{ static_cast<float>(y_axis_top.x), static_cast<float>(y_axis_top.y)
  //   },
  //              sf::Color::Red)
  // };
  // sf::Vertex x_axis[]{ sf::Vertex(sf::Vector2f{ static_cast<float>(x_axis_start.x),
  //                                               static_cast<float>(x_axis_start.y) },
  //                                 sf::Color::Blue),
  //                      sf::Vertex(sf::Vector2f{ static_cast<float>(x_axis_end.x),
  //                                               static_cast<float>(x_axis_end.y) },
  //                                 sf::Color::Blue) };

  // Main game loop
  bool bt_mid_pressed = false;
  int pt_start_x{}, pt_start_y{};
  while (window.isOpen())
  {
    sf::Event event;

    // Handle events
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close(); // Close window if the user clicks the close button
      }
      else if (event.type == sf::Event::MouseMoved)
      {
        auto coords = world.ConvertToWorld(event.mouseMove.x, event.mouseMove.y);
        text_coords.setString(std::format("{:6d}, {:6d}\n{:2.4f}, {:2.4f}\nPressing: {}",
                                          event.mouseMove.x,
                                          event.mouseMove.y,
                                          coords.x,
                                          coords.y,
                                          bt_mid_pressed));
        if (bt_mid_pressed)
        {
          int end_x = event.mouseMove.x;
          int end_y = event.mouseMove.y;
          auto p1 = world.ConvertToWorld(pt_start_x, pt_start_y);
          auto p2 = world.ConvertToWorld(end_x, end_y);
          world.MoveHorizontally(-(p2.x - p1.x));
          world.MoveVertically(-(p2.y - p1.y));
          pt_start_x = end_x;
          pt_start_y = end_y;
        }
      }
      else if (event.type == sf::Event::MouseWheelScrolled)
      {
        if (event.mouseWheelScroll.delta < 0)
          world.ZoomOut();
        else
          world.ZoomIn();
      }
      else if (event.type == sf::Event::MouseButtonPressed)
      {
        if (!bt_mid_pressed && event.mouseButton.button == sf::Mouse::Button::Middle)
        {
          bt_mid_pressed = true;
          pt_start_x = event.mouseButton.x;
          pt_start_y = event.mouseButton.y;
        }
        auto pt_coords = world.ConvertToWorld(event.mouseButton.x, event.mouseButton.y);
        circles.emplace_back(pt_coords.x, pt_coords.y);
        // circles.emplace_back(sf::Vector2f{ static_cast<float>(event.mouseButton.x),
        // static_cast<float>(event.mouseButton.y) });
      }
      else if (event.type == sf::Event::MouseButtonReleased)
      {
        if (bt_mid_pressed && event.mouseButton.button == sf::Mouse::Button::Middle)
          bt_mid_pressed = false;
      }
      else if (event.type == sf::Event::KeyReleased)
      {
        constexpr auto STEP = 0.01;
        if (event.key.code == sf::Keyboard::A)
          world.MoveHorizontally(-STEP);
        else if (event.key.code == sf::Keyboard::D)
          world.MoveHorizontally(+STEP);
        else if (event.key.code == sf::Keyboard::W)
          world.MoveVertically(+STEP);
        else if (event.key.code == sf::Keyboard::S)
          world.MoveVertically(-STEP);
      }
    }

    // Clear the screen with a black color
    window.clear(sf::Color::Black);

    // Draw the circle
    // for (const auto& c : circles)
    // {
    //   sf::CircleShape cs{ 1.0f, 10 };
    //   const auto screen_pos = world.ConvertToScreen(c.x, c.y);
    //   cs.setPosition(screen_pos.x, screen_pos.y);
    //   window.draw(cs);
    // }

    std::ranges::for_each(circles, [&](auto&& c) { ObjectDrawer::DrawPoint(window, world, c); });
    ObjectDrawer::DrawLine(window, world, l_x);
    ObjectDrawer::DrawLine(window, world, l_y);

    window.draw(text_coords);
    window.draw(text_zoom);

    // window.draw(y_axis, 2, sf::Lines);
    // window.draw(x_axis, 2, sf::Lines);

    // Display everything that was drawn
    window.display();
  }

  return 0;
}
