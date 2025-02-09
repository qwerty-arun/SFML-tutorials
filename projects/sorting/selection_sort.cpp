#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <vector>
#include <thread> // For delay

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Selection Sort Visualization");

    const int numRects = 75;
    float width = 3.0f;
    sf::RectangleShape rectangles[numRects];

    // Initialize rectangles with random heights
    for (int i = 0; i < numRects; i++) {
        /*float height = 20 * (rand() % 10 + 1); //seems to have similar heights*/
        float height = 50 + rand()%300;
        rectangles[i].setSize(sf::Vector2f(width, height));
        rectangles[i].setPosition(30.0f + (width + 2) * i, 450 - height);
        rectangles[i].setFillColor(sf::Color::White);
    }

    int i = 0, j = 0, smallestIdx = 0;  // Variables for sorting state
    bool sorting = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Selection Sort (Step-by-step)
        if (sorting) {
            if (i < numRects - 1) {
                if (j < numRects) {
                    if (rectangles[j].getSize().y < rectangles[smallestIdx].getSize().y) {
                        smallestIdx = j; // Update smallest index
                    }
                    j++; // Move to next element in inner loop
                } else {
                    // Swap once the smallest element is found
                    sf::Vector2f sizeI = rectangles[i].getSize();
                    sf::Vector2f sizeSmallest = rectangles[smallestIdx].getSize();
                    
                    // Swap heights
                    rectangles[i].setSize(sf::Vector2f(sizeI.x, sizeSmallest.y));
                    rectangles[smallestIdx].setSize(sf::Vector2f(sizeSmallest.x, sizeI.y));

                    // Reposition correctly (to maintain top alignment)
                    rectangles[i].setPosition(rectangles[i].getPosition().x, 450 - rectangles[i].getSize().y);
                    rectangles[smallestIdx].setPosition(rectangles[smallestIdx].getPosition().x, 450 - rectangles[smallestIdx].getSize().y);

                    // Move to next element in outer loop
                    i++;
                    j = i + 1;
                    smallestIdx = i;
                }
            } else {
                sorting = false; // Sorting complete
            }
        }

        // Draw rectangles
        for (int k = 0; k < numRects; k++) {
            window.draw(rectangles[k]);
        }

        window.display();

        // Slow down the sorting for visualization
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    return 0;
}

