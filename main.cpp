#include "domain/geometry/world_converter.hpp"
#include "domain/model.hpp"
#include "draw/object_drawer.hpp"
#include "io/model_loader.hpp"
#include "utils/aliases.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <format>

Line l_x{ Point{ 0, -1000 }, Point{ 0, 1000 } };
Line l_y{ Point{ -1000, 0 }, Point{ 1000, 0 } };

int main()
{
  // Create a window with the resolution of 800x600
  sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML Window");

  // Set the frame rate limit to 60 FPS
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.openFromFile("fonts/Inter-Regular.ttf"))
  {
    return -1;
  }
  sf::Text text_coords{ font };
  text_coords.setCharacterSize(12);
  text_coords.setFillColor(sf::Color::White);
  sf::Text text_zoom = text_coords;

  World world{ window.getSize().x, window.getSize().y };
  world.MoveVertically(-0.1);
  world.MoveHorizontally(-0.1);

  Ptr<Model> model = ModelLoader::Read("assets/interlagos_pts.txt");

  // Main game loop
  bool bt_mid_pressed = false;
  int pt_start_x{}, pt_start_y{};
  while (window.isOpen())
  {
    // Handle events
    while (const auto event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close(); // Close window if the user clicks the close button
      }
      else if (event->is<sf::Event::MouseMoved>())
      {
        const auto x = event->getIf<sf::Event::MouseMoved>()->position.x;
        const auto y = event->getIf<sf::Event::MouseMoved>()->position.y;
        auto coords = world.ConvertToWorld(x, y);
        text_coords.setString(std::format("{:6d}, {:6d}\n{:2.4f}, {:2.4f}\nPressing: {}",
                                          x,
                                          y,
                                          coords.x,
                                          coords.y,
                                          bt_mid_pressed));
        if (bt_mid_pressed)
        {
          int end_x = x;
          int end_y = y;
          auto p1 = world.ConvertToWorld(pt_start_x, pt_start_y);
          auto p2 = world.ConvertToWorld(end_x, end_y);
          world.MoveHorizontally(-(p2.x - p1.x));
          world.MoveVertically(-(p2.y - p1.y));
          pt_start_x = end_x;
          pt_start_y = end_y;
        }
      }
      else if (event->is<sf::Event::MouseWheelScrolled>())
      {
        if (event->getIf<sf::Event::MouseWheelScrolled>()->delta < 0)
          world.ZoomOut();
        else
          world.ZoomIn();
      }
      else if (event->is<sf::Event::MouseButtonPressed>())
      {
        const auto pos = event->getIf<sf::Event::MouseButtonPressed>()->position;
        const auto bt = event->getIf<sf::Event::MouseButtonPressed>()->button;
        if (!bt_mid_pressed && bt == sf::Mouse::Button::Middle)
        {
          bt_mid_pressed = true;
          pt_start_x = pos.x;
          pt_start_y = pos.y;
        }
        //        auto pt_coords = world.ConvertToWorld(event.mouseButton.x, event.mouseButton.y);
        //        circles.emplace_back(pt_coords.x, pt_coords.y);
        // circles.emplace_back(sf::Vector2f{ static_cast<float>(event.mouseButton.x),
        // static_cast<float>(event.mouseButton.y) });
      }
      else if (event->is<sf::Event::MouseButtonReleased>())
      {
        if (bt_mid_pressed &&
            event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Middle)
          bt_mid_pressed = false;
      }
      else if (event->is<sf::Event::KeyReleased>())
      {
        auto key = event->getIf<sf::Event::KeyReleased>()->code;
        constexpr auto STEP = 0.01;
        if (key == sf::Keyboard::Key::A)
          world.MoveHorizontally(-STEP);
        else if (key == sf::Keyboard::Key::D)
          world.MoveHorizontally(+STEP);
        else if (key == sf::Keyboard::Key::W)
          world.MoveVertically(+STEP);
        else if (key == sf::Keyboard::Key::S)
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

    //    std::ranges::for_each(circles, [&](auto&& c) { ObjectDrawer::DrawPoint(window, world, c);
    //    });
    ObjectDrawer::DrawLine(window, world, l_x);
    ObjectDrawer::DrawLine(window, world, l_y);
    ObjectDrawer::DrawModel(window, world, model);

    window.draw(text_coords);
    window.draw(text_zoom);

    // window.draw(y_axis, 2, sf::Lines);
    // window.draw(x_axis, 2, sf::Lines);

    // Display everything that was drawn
    window.display();
  }

  return 0;
}
