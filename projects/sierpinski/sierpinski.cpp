#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

// Function to compute the midpoint of two points
sf::Vector2f midpoint(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return sf::Vector2f((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
}

// Recursive function to draw Sierpiński Triangle
void drawSierpinski(sf::RenderWindow& window, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, int depth) {
    if (depth == 0) {
        // Base case: Draw a simple triangle
        sf::ConvexShape triangle(3);
        triangle.setPoint(0, p1);
        triangle.setPoint(1, p2);
        triangle.setPoint(2, p3);
        triangle.setFillColor(sf::Color::White);
        window.draw(triangle);
    } else {
        // Find midpoints
        sf::Vector2f m1 = midpoint(p1, p2);
        sf::Vector2f m2 = midpoint(p2, p3);
        sf::Vector2f m3 = midpoint(p3, p1);

        // Recursively draw smaller triangles
        drawSierpinski(window, p1, m1, m3, depth - 1);
        drawSierpinski(window, p2, m1, m2, depth - 1);
        drawSierpinski(window, p3, m2, m3, depth - 1);
    }
}

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sierpiński Triangle - SFML");

    // Define main triangle vertices
    sf::Vector2f p1(400, 50);   // Top vertex
    sf::Vector2f p2(100, 700);  // Bottom-left
    sf::Vector2f p3(700, 700);  // Bottom-right

    int depth = 5; // Change this value to increase/decrease detail

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.key.code == sf::Keyboard::Up && depth < 15)
                depth++;
            if(event.key.code == sf::Keyboard::Down && depth >0)
                depth--;
        }

        window.clear(sf::Color::Black);
        drawSierpinski(window, p1, p2, p3, depth);
        window.display();
    }

    return 0;
}

