#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Line Drawing");

    std::vector<sf::Vertex> lines;
    bool drawing = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                lines.push_back(sf::Vertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), sf::Color::White));
                drawing = true;
            }

            if (event.type == sf::Event::MouseMoved && drawing) {
                lines.push_back(sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), sf::Color::White));
            }

            if (event.type == sf::Event::MouseButtonReleased)
                drawing = false;
        }

        window.clear();
        if (!lines.empty())
            window.draw(lines.data(), lines.size(), sf::LinesStrip);
        window.display();
    }

    return 0;
}
