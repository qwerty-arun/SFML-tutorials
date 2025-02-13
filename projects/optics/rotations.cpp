#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "setOrigin Example");

    // Create a rectangle (size: 100x50)
    sf::RectangleShape rect(sf::Vector2f(100.f, 50.f));
    rect.setPosition(250.f, 250.f); // Set center position
    rect.setFillColor(sf::Color::Green);

    // Default origin (top-left)
    sf::RectangleShape rectDefault = rect;

    // Center origin
    sf::RectangleShape rectCenter = rect;
    rectCenter.setOrigin(50.f, 25.f); // (width/2, height/2)

    // Bottom-right origin
    sf::RectangleShape rectBottomRight = rect;
    rectBottomRight.setOrigin(100.f, 50.f); // (width, height)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Rotate each rectangle
        rectDefault.rotate(1.f);
        rectCenter.rotate(1.f);
        rectBottomRight.rotate(1.f);

        window.clear();
        /*window.draw(rectDefault);*/
        window.draw(rectCenter);
        /*window.draw(rectBottomRight);*/
        window.display();
    }

    return 0;
}

