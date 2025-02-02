#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Moving Circle");

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(175.f, 175.f);  // Start position

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            circle.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            circle.move(5.f, 0.f);
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
