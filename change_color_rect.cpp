#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Click to Change Color");

    sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(150.f, 150.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    
                    if (rect.getGlobalBounds().contains(mousePos)) {
                        rect.setFillColor(sf::Color::Magenta);  // Change color on click
                    }
                }
            }
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}

