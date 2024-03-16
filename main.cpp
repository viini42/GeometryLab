#include <SFML/Graphics.hpp>

int main()
{
  // Create a window with the resolution of 800x600
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

  // Set the frame rate limit to 60 FPS
  window.setFramerateLimit(60);

  // Create a circle shape with a radius of 50 pixels
  sf::CircleShape circle(50.0f);
  circle.setFillColor(sf::Color::Green); // Set the fill color to green
  circle.setPosition(375, 275);          // Set position (center of the window)

  // Main game loop
  while (window.isOpen())
  {
    sf::Event event;

    // Handle events
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close(); // Close window if the user clicks the close button
    }

    // Clear the screen with a black color
    window.clear(sf::Color::Black);

    // Draw the circle
    window.draw(circle);

    // Display everything that was drawn
    window.display();
  }

  return 0;
}
