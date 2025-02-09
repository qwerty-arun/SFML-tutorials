#include <SFML/Graphics.hpp>
#include <cmath>

// Function to create a thick line using Quads
sf::VertexArray createThickLine(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color) {
    sf::VertexArray quad(sf::Quads, 4);

    sf::Vector2f direction = end - start; // Direction vector
    sf::Vector2f unitDir = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize
    sf::Vector2f normal(-unitDir.y, unitDir.x); // Perpendicular to direction

    // Scale normal by half the thickness
    normal *= thickness / 2.0f;

    // Define the four corners of the quad
    quad[0].position = start + normal;
    quad[1].position = start - normal;
    quad[2].position = end - normal;
    quad[3].position = end + normal;

    // Set color
    for (int i = 0; i < 4; ++i)
        quad[i].color = color;

    return quad;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Thick Line");

    // Create a thick line
    sf::VertexArray thickLine = createThickLine({100, 200}, {500, 300}, 10.0f, sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(thickLine); // Draw thick line
        window.display();
    }

    return 0;
}

