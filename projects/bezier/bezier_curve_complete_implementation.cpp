#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float POINT_RADIUS = 6.0f; // Radius for control points

// Compute a point on the Bézier curve using De Casteljau's algorithm
sf::Vector2f deCasteljau(const std::vector<sf::Vector2f>& points, float t) {
    std::vector<sf::Vector2f> temp = points;
    int n = temp.size() - 1;

    for (int r = 1; r <= n; ++r) {
        for (int i = 0; i <= n - r; ++i) {
            temp[i] = (1 - t) * temp[i] + t * temp[i + 1];
        }
    }
    return temp[0];
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier Curve Editor");
    std::vector<sf::Vector2f> controlPoints;

    bool dragging = false;
    int draggedPointIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Left-click: Add new control point OR start dragging if near an existing point
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                // Check if we clicked near an existing control point
                for (size_t i = 0; i < controlPoints.size(); ++i) {
                    if (std::hypot(mousePos.x - controlPoints[i].x, mousePos.y - controlPoints[i].y) < POINT_RADIUS * 2) {
                        dragging = true;
                        draggedPointIndex = i;
                        break;
                    }
                }

                // If no dragging, add a new control point
                if (!dragging) {
                    controlPoints.push_back(mousePos);
                }
            }

            // Right-click: Remove last control point
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                if (!controlPoints.empty()) {
                    controlPoints.pop_back();
                }
            }

            // Mouse release: Stop dragging
            if (event.type == sf::Event::MouseButtonReleased) {
                dragging = false;
                draggedPointIndex = -1;
            }
        }

        // If dragging, update the position of the selected control point
        if (dragging && draggedPointIndex != -1) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            controlPoints[draggedPointIndex] = sf::Vector2f(mousePos.x, mousePos.y);
        }

        window.clear(sf::Color::Black);

        // Draw control polygon (thin gray lines connecting control points)
        if (controlPoints.size() > 1) {
            sf::VertexArray controlPolygon(sf::LineStrip);
            for (auto& point : controlPoints) {
                controlPolygon.append(sf::Vertex(point, sf::Color(100, 100, 100))); // Gray lines
            }
            window.draw(controlPolygon);
        }

        // Draw Bézier curve
        if (controlPoints.size() > 1) {
            sf::VertexArray bezierCurve(sf::LineStrip);
            for (float t = 0; t <= 1; t += 0.005f) { // Higher density for smoothness
                bezierCurve.append(sf::Vertex(deCasteljau(controlPoints, t), sf::Color::White));
            }
            window.draw(bezierCurve);
        }

        // Draw control points
        for (auto& point : controlPoints) {
            sf::CircleShape shape(POINT_RADIUS);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(point.x - POINT_RADIUS, point.y - POINT_RADIUS);
            window.draw(shape);
        }

        window.display();
    }
    return 0;
}

