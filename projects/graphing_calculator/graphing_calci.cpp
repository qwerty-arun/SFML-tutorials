#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graphing Calculator", sf::Style::Resize | sf::Style::Close);
    
    std::vector<sf::Vertex> graph1Stroke;
    std::vector<sf::Vertex> graph2Stroke;
    std::vector<sf::Vertex> graph3Stroke;

    sf::Vector2f offset_1(50.0f, 80.0f);
    sf::Vector2f offset_2(50.0f, 200.0f);
    sf::Vector2f offset_3(50.0f, 300.0f);

    // Generate first sine wave
    for (float i = 0.0f; i <= 19.f; i += 0.01f) {
        graph1Stroke.push_back(sf::Vertex(sf::Vector2f(20 * i + offset_1.x, -20 * sin(1 * i) + offset_1.y), sf::Color::Yellow));
    }

    // Generate second sine wave
    for (float i = 0.0f; i <= 19.f; i += 0.01f) {
        graph2Stroke.push_back(sf::Vertex(sf::Vector2f(20 * i + offset_2.x, -20 * sin(3* i) + offset_2.y), sf::Color::Red));
    }

    // Generate third wave (Sum of first two waves)
    for (size_t i = 0; i < graph1Stroke.size(); i++) {
        float x = graph1Stroke[i].position.x; // X-coordinates should match
        float y = graph1Stroke[i].position.y + (graph2Stroke[i].position.y - offset_2.y); // Sum of Y values
        graph3Stroke.push_back(sf::Vertex(sf::Vector2f(x, y + offset_3.y), sf::Color::Green));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw first sine wave
        window.draw(&graph1Stroke[0], graph1Stroke.size(), sf::LineStrip);
        // Draw second sine wave
        window.draw(&graph2Stroke[0], graph2Stroke.size(), sf::LineStrip);
        // Draw third (sum) wave
        window.draw(&graph3Stroke[0], graph3Stroke.size(), sf::LineStrip);

        window.display();
    }

    return 0;
}
