#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "deltaTime Example");

    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(100.f, 200.f); // Initial position

    sf::Clock clock; // Clock to measure time

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate deltaTime
        float deltaTime = clock.restart().asSeconds(); // Time since last frame

        // Move the rectangle at 200 pixels per second
        float speed = 200.f; // Pixels per second
        /*rectangle.move(speed * deltaTime, 0); // Moves in X-direction*/
        float angle{45};
        rectangle.rotate(5*angle*deltaTime);

        /*rectangle.rotate(angle);*/
        angle++;
        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
