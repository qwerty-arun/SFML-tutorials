#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "View Panning");
    
    sf::View view = window.getDefaultView(); // Default camera
    sf::RectangleShape box(sf::Vector2f(100, 100));
    box.setFillColor(sf::Color::Red);
    box.setPosition(400, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the view using arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-5.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(5.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0.f, -5.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0.f, 5.f);

        window.setView(view);
        window.clear();
        window.draw(box);
        window.display();
    }
    return 0;
}

