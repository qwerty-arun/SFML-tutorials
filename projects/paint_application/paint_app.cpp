#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Smooth Paint App");

    sf::VertexArray lines(sf::LineStrip); // Stores the line segments
    sf::Color currentColor = sf::Color::Black;  // Default color

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Change color on keypress
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) currentColor = sf::Color::Red;
                if (event.key.code == sf::Keyboard::G) currentColor = sf::Color::Green;
                if (event.key.code == sf::Keyboard::B) currentColor = sf::Color::Blue;
                if (event.key.code == sf::Keyboard::Y) currentColor = sf::Color::Yellow;
                if (event.key.code == sf::Keyboard::K) currentColor = sf::Color::Black;
            }
        }

        // Draw only when the left mouse button is held
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            lines.append(sf::Vertex(sf::Vector2f(mousePos), currentColor));
        }

        window.clear(sf::Color::White);
        window.draw(lines);  // Draw the smooth line
        window.display();
    }
    return 0;
}
