#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Recursive De Casteljau's algorithm for Bézier curves
sf::Vector2f deCasteljau(const std::vector<sf::Vector2f>& points, float t) {
    std::vector<sf::Vector2f> temp = points;
    int n = temp.size() - 1;

    for (int r = 1; r <= n; ++r) {
        for (int i = 0; i <= n - r; ++i) {
            temp[i] = (1 - t) * temp[i] + t * temp[i + 1];
        }
    }
    return temp[0]; // Final point on the Bézier curve
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier Curve Drawer");
    std::vector<sf::Vector2f> controlPoints;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Left-click to add control points
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                controlPoints.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }

            // Right-click to remove the last control point
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                if (!controlPoints.empty())
                    controlPoints.pop_back();
            }
        }

        window.clear(sf::Color::Black);

        // Draw control points
        for (auto& point : controlPoints) {
            sf::CircleShape shape(5);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(point.x - 5, point.y - 5);
            window.draw(shape);
        }

        // Draw thin lines connecting control points
        if (controlPoints.size() > 1) {
            sf::VertexArray controlPolygon(sf::LineStrip);
            for (auto& point : controlPoints) {
                controlPolygon.append(sf::Vertex(point, sf::Color(100, 100, 100))); // Grey lines
            }
            window.draw(controlPolygon);
        }

        // Draw Bézier curve if we have at least 2 control points
        if (controlPoints.size() > 1) {
            sf::VertexArray bezierCurve(sf::LineStrip);
            for (float t = 0; t <= 1; t += 0.005f) { // Increase density for smoothness
                bezierCurve.append(sf::Vertex(deCasteljau(controlPoints, t), sf::Color::White));
            }
            window.draw(bezierCurve);
        }

        window.display();
    }
    return 0;
}

