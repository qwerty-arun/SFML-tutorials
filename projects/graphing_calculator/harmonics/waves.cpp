#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float PI = 3.14159265358979323846;
const int HARMONICS = 15; // Number of odd harmonics to include

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 500), "Square Wave Approximation", sf::Style::Close);

    std::vector<sf::Vertex> fundamentalWave; // Stores fundamental sine wave
    std::vector<std::vector<sf::Vertex>> harmonics; // Stores all harmonic components
    std::vector<sf::Vertex> squareWave; // Stores approximated square wave

    sf::Vector2f offset_1(50.0f, 100.0f);
    sf::Vector2f offset_2(50.0f, 250.0f);
    sf::Vector2f offset_3(50.0f, 400.0f);

    float amplitude = 40.0f; // Adjust amplitude of the wave
    float frequency = 1.0f;  // Base frequency of the sine wave

    // Generate the fundamental sine wave and draw, not used for calculation
    for (float i = 0.0f; i <= 19.0f; i += 0.01f) {
        float y = amplitude * sin(frequency * i);
        fundamentalWave.push_back(sf::Vertex(sf::Vector2f(20 * i + offset_1.x, -y + offset_1.y), sf::Color::Yellow));
    }

    // Generate harmonic waves and draw, not used for calculation
    harmonics.resize(HARMONICS);
    for (int h = 1, n = 1; h <= HARMONICS; h++, n += 2) { // Only odd harmonics
        for (float i = 0.0f; i <= 19.0f; i += 0.01f) {
            float y = (amplitude * sin(n * frequency * i)) / n; // Harmonic component
            harmonics[h - 1].push_back(sf::Vertex(sf::Vector2f(20 * i + offset_2.x, -y + offset_2.y), sf::Color::Red));
        }
    }

    // Generate the square wave approximation by summing harmonics
    for (float i = 0.0f; i <= 19.0f; i += 0.01f) {
        float y = 0.0f;
        for (int h = 1, n = 1; h <= HARMONICS; h++, n += 2) {
            y += (amplitude * sin(n * frequency * i)) / n; // Sum odd harmonics
        }
        y = (4 / PI) * y; // Scaling factor for square wave
        squareWave.push_back(sf::Vertex(sf::Vector2f(20 * i + offset_3.x, -y + offset_3.y), sf::Color::Green));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw fundamental wave
        window.draw(&fundamentalWave[0], fundamentalWave.size(), sf::LineStrip);

        // Draw harmonics
        for (const auto& harmonic : harmonics) {
            window.draw(&harmonic[0], harmonic.size(), sf::LineStrip);
        }

        // Draw square wave approximation
        window.draw(&squareWave[0], squareWave.size(), sf::LineStrip);

        window.display();
    }

    return 0;
}
