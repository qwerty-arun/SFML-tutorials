#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Smooth Paint App");

    std::vector<sf::VertexArray> strokes; // Stores multiple independent strokes
    sf::VertexArray currentStroke(sf::LineStrip); // Stores the current stroke
    sf::Color currentColor = sf::Color::Black;
    bool isDrawing = false; // Flag to check if the mouse is pressed

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Change color when a key is pressed
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) currentColor = sf::Color::Red;
                if (event.key.code == sf::Keyboard::G) currentColor = sf::Color::Green;
                if (event.key.code == sf::Keyboard::B) currentColor = sf::Color::Blue;
                if (event.key.code == sf::Keyboard::Y) currentColor = sf::Color::Yellow;
                if (event.key.code == sf::Keyboard::K) currentColor = sf::Color::Black;
            }

            // When mouse button is pressed, start a new stroke
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                currentStroke = sf::VertexArray(sf::LineStrip); // Reset stroke
                isDrawing = true;
            }

            // When mouse button is released, store the stroke in the vector
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (currentStroke.getVertexCount() > 1) { // Avoid storing empty strokes
                    strokes.push_back(currentStroke);
                }
                isDrawing = false;
            }
        }

        // Add new points to the current stroke only if the mouse is held
        if (isDrawing) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            currentStroke.append(sf::Vertex(sf::Vector2f(mousePos), currentColor));
        }

        window.clear(sf::Color::White);

        // Draw all previous strokes
        for (auto& stroke : strokes) {
            window.draw(stroke);
        }

        // Draw the current stroke while the user is still drawing
        if (isDrawing) {
            window.draw(currentStroke);
        }

        window.display();
    }
    return 0;
}
