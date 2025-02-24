#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

sf::Vector2f quadraticBezier(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2) {
    float u = 1 - t;
    return u * u * p0 + 2 * u * t * p1 + t * t * p2;
}

sf::Vector2f cubicBezier(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
    float u = 1 - t;
    return u * u * u * p0 + 3 * u * u * t * p1 + 3 * u * t * t * p2 + t * t * t * p3;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier Curve Drawer");
    std::vector<sf::Vector2f> controlPoints;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Left-click to add a control point
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (controlPoints.size() < 4) // Limit to 4 points for cubic Bezier
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
        for (auto &point : controlPoints) {
            sf::CircleShape shape(5);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(point.x - 5, point.y - 5);
            window.draw(shape);
        }

        // Draw Bézier curve if we have enough points
        if (controlPoints.size() >= 3) {
            sf::VertexArray bezierCurve(sf::LineStrip);
            for (float t = 0; t <= 1; t += 0.01f) {
                if (controlPoints.size() == 3) {
                    bezierCurve.append(sf::Vertex(quadraticBezier(t, controlPoints[0], controlPoints[1], controlPoints[2]), sf::Color::White));
                } else if (controlPoints.size() == 4) {
                    bezierCurve.append(sf::Vertex(cubicBezier(t, controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]), sf::Color::Cyan));
                }
            }
            window.draw(bezierCurve);
        }

        window.display();
    }
    return 0;
}

