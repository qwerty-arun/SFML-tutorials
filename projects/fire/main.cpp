#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const int gridWidth = 50;
const int gridHeight = 50;
const int cellSize = 10;
const float diffusionRate = 0.1f;
const float maxTemp = 1000.f;

using namespace sf;

// Convert temperature to a color (blue = cold, red = hot)
Color temperatureToColor(float temp) {
    float t = std::min(std::max(temp / maxTemp, 0.f), 1.f);
    Uint8 r = static_cast<Uint8>(255 * t);
    Uint8 g = static_cast<Uint8>(255 * (1 - std::abs(t - 0.5f) * 2));
    Uint8 b = static_cast<Uint8>(255 * (1 - t));
    return Color(r, g, b);
}

int main() {
    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "2D Heat Diffusion");
    window.setFramerateLimit(60);

    // 2D temperature grid
    std::vector<std::vector<float>> temperature(gridHeight, std::vector<float>(gridWidth, 0.f));
    std::vector<std::vector<float>> newTemperature = temperature;

    // Create cell shapes
    RectangleShape cell(Vector2f(cellSize - 1, cellSize - 1)); // 1 px padding for grid look

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Add heat with mouse click
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            int x = mousePos.x / cellSize;
            int y = mousePos.y / cellSize;
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                temperature[y][x] = maxTemp;
            }
        }

        // Apply heat diffusion
        for (int y = 1; y < gridHeight - 1; ++y) {
            for (int x = 1; x < gridWidth - 1; ++x) {
                newTemperature[y][x] = temperature[y][x] + diffusionRate * (
                    temperature[y + 1][x] +
                    temperature[y - 1][x] +
                    temperature[y][x + 1] +
                    temperature[y][x - 1] -
                    4 * temperature[y][x]
                );
            }
        }

        // Swap temperature buffers
        temperature.swap(newTemperature);

        // Draw grid
        window.clear();
        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(temperatureToColor(temperature[y][x]));
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}

