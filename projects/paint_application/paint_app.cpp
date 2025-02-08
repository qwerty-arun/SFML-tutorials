// Features: independent drawings (freehand), color palette for selecting colors, clear button to erase everything
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Smooth Paint App", sf::Style::Resize | sf::Style::Close);
    
    std::vector<sf::VertexArray> strokes; // Stores all the drawn strokes
    sf::VertexArray currentStroke(sf::LineStrip); // Stores the current stroke
    sf::Color currentColor = sf::Color::Black; // Default color

    bool isDrawing = false; // Flag for drawing
    bool eraserOn = false;  // Flag for eraser mode

    // Color Palette
    sf::RectangleShape colorPalette[5];
    sf::Color colors[5] = { sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Green, sf::Color::Black };
    
    for (int i = 0; i < 5; i++) {
        colorPalette[i].setSize(sf::Vector2f(40.0f, 40.0f));
        colorPalette[i].setFillColor(colors[i]);
        colorPalette[i].setPosition(460.0f, i * 40.0f);
    }

    // Clear Button
    sf::RectangleShape clearBox;
    clearBox.setSize(sf::Vector2f(40.0f, 40.0f));
    clearBox.setFillColor(sf::Color(128, 128, 128)); // Gray
    clearBox.setPosition(0.f, 0.f);

    // Eraser Button
    sf::RectangleShape eraserBox;
    eraserBox.setSize(sf::Vector2f(40.0f, 40.0f));
    eraserBox.setFillColor(sf::Color(200, 200, 200)); // Light Gray
    eraserBox.setPosition(40.f, 0.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                // Check if a color button is clicked
                for (int i = 0; i < 5; i++) {
                    if (colorPalette[i].getGlobalBounds().contains(mousePosF)) {
                        currentColor = colors[i];
                        eraserOn = false; // Turn off eraser mode
                    }
                }

                // Check if the clear button is clicked
                if (clearBox.getGlobalBounds().contains(mousePosF)) {
                    strokes.clear();
                    eraserOn = false;
                }

                // Check if the eraser button is clicked
                if (eraserBox.getGlobalBounds().contains(mousePosF)) {
                    eraserOn = true;
                }

                // Start a new stroke if drawing mode is active
                if (!eraserOn) {
                    currentStroke = sf::VertexArray(sf::LineStrip);
                    isDrawing = true;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (isDrawing && currentStroke.getVertexCount() > 1) {
                    strokes.push_back(currentStroke);
                }
                isDrawing = false;
            }
        }

        // Drawing logic
        if (isDrawing && !eraserOn) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            currentStroke.append(sf::Vertex(sf::Vector2f(mousePos), currentColor));
        }

        // Eraser logic
        if (eraserOn && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f eraserPos(mousePos.x, mousePos.y);
            float eraserRadius = 10.0f;

            for (auto& stroke : strokes) {
                for (size_t i = 0; i < stroke.getVertexCount(); ++i) {
                    sf::Vector2f point = stroke[i].position;
                    if (std::hypot(point.x - eraserPos.x, point.y - eraserPos.y) < eraserRadius) {
                        stroke[i].color = sf::Color::White; // "Erase" by changing color to background
                    }
                }
            }
        }

        // Rendering
        window.clear(sf::Color::White);

        // Draw all previous strokes
        for (const auto& stroke : strokes) {
            window.draw(stroke);
        }

        // Draw the current stroke
        if (isDrawing) {
            window.draw(currentStroke);
        }

        // Draw UI elements
        for (const auto& colorBox : colorPalette) {
            window.draw(colorBox);
        }
        window.draw(clearBox);
        window.draw(eraserBox);

        window.display();
    }

    return 0;
}
