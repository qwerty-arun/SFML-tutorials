#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Vertex Array - Square");

    sf::VertexArray square(sf::Quads, 4);
    sf::Vector2f size(50, 50);  // Square width & height
    sf::Vector2f position(250, 250); // Initial position
    sf::Vector2f velocity(-0.5f, 0.6f); // Movement speed

    // Initialize square position
    square[0].position = position;
    square[1].position = position + sf::Vector2f(0, size.y);
    square[2].position = position + sf::Vector2f(size.x, size.y);
    square[3].position = position + sf::Vector2f(size.x, 0);

    // Seed for random colors
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the square
        for (int i = 0; i < 4; i++) {
            square[i].position += velocity;
        }

        // Check for boundary collision
        if (square[0].position.x <= 0 || square[2].position.x >= window.getSize().x) {
            velocity.x = -velocity.x;
            // Change color on bounce
            sf::Color newColor(rand() % 256, rand() % 256, rand() % 256);
            for (int i = 0; i < 4; i++)
                square[i].color = newColor;
        }
        if (square[0].position.y <= 0 || square[2].position.y >= window.getSize().y) {
            velocity.y = -velocity.y;
            // Change color on bounce
            sf::Color newColor(rand() % 256, rand() % 256, rand() % 256);
            for (int i = 0; i < 4; i++)
                square[i].color = newColor;
        }

        window.clear();
        window.draw(square);
        window.display();
    }
    return 0;
}
