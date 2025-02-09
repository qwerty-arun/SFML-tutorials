#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

const int NUM_RECTANGLES = 80;
const float RECT_WIDTH = 10.0f;
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

// Function to swap heights of two rectangles
void swapHeights(sf::RectangleShape &rect1, sf::RectangleShape &rect2) {
    float tempHeight = rect1.getSize().y;
    rect1.setSize({RECT_WIDTH, rect2.getSize().y});
    rect1.setPosition(rect1.getPosition().x, WINDOW_HEIGHT - rect2.getSize().y);

    rect2.setSize({RECT_WIDTH, tempHeight});
    rect2.setPosition(rect2.getPosition().x, WINDOW_HEIGHT - tempHeight);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Selection Sort Visualization");

    // Create an array of rectangles
    std::vector<sf::RectangleShape> rectangles(NUM_RECTANGLES);

    // Initialize rectangles with random heights
    for (int i = 0; i < NUM_RECTANGLES; ++i) {
        float height = 20 * (rand() % 10 + 1); // Random height between 20 and 200
        rectangles[i].setSize({RECT_WIDTH, height});
        rectangles[i].setPosition(100 + i * (RECT_WIDTH + 5), WINDOW_HEIGHT - height);
        rectangles[i].setFillColor(sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Selection Sort Animation
        for (int i = 0; i < NUM_RECTANGLES - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < NUM_RECTANGLES; ++j)
                if (rectangles[j].getSize().y < rectangles[minIndex].getSize().y)
                    minIndex = j;

            if (minIndex != i) { 
                swapHeights(rectangles[i], rectangles[minIndex]);
            }

            // Drawing part
            window.clear();
            for (auto &rect : rectangles)
                window.draw(rect);
            window.display();

            // Add delay for visualization
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    return 0;
}

