#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <limits>

using namespace sf;
using namespace std;

// ---------------------------- Torch Class ----------------------------
class Torch {
public:
    CircleShape torch;
    Vector2f position;

    Torch() {
        torch.setRadius(8);
        torch.setOrigin(8, 8);
        torch.setFillColor(Color::Yellow);
    }

    void update(RenderWindow& window) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            position = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            torch.setPosition(position);
        }
    }

    void draw(RenderWindow& window) {
        window.draw(torch);
    }

    Vector2f getPosition() const {
        return position;
    }
};

// ---------------------------- Wall Class ----------------------------
class Wall {
public:
    Vector2f a, b;
    VertexArray shape;

    Wall(Vector2f start, Vector2f end) : a(start), b(end) {
        shape = VertexArray(Lines, 2);
        shape[0].position = a;
        shape[0].color = Color::Cyan;
        shape[1].position = b;
        shape[1].color = Color::Cyan;
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }
};

// ---------------------------- Helper Function ----------------------------
bool getIntersection(Vector2f rayOrigin, Vector2f rayDir, Vector2f wallA, Vector2f wallB, Vector2f& intersection) {
    float x1 = wallA.x, y1 = wallA.y;
    float x2 = wallB.x, y2 = wallB.y;
    float x3 = rayOrigin.x, y3 = rayOrigin.y;
    float x4 = rayOrigin.x + rayDir.x, y4 = rayOrigin.y + rayDir.y;

    float den = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (den == 0) return false; // parallel lines

    float t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) / den;
    float u = -((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3)) / den;

    if (t >= 0 && t <= 1 && u >= 0) {
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return true;
    }
    return false;
}

// ---------------------------- Beam Class ----------------------------
class Beam {
public:
    vector<VertexArray> beams;
    const int rayCount = 360;

    void update(const Vector2f& sourcePosition, const vector<Wall>& walls) {
        beams.clear();

        for (int i = 0; i < rayCount; ++i) {
            float angle = i * 2 * 3.14159f / rayCount;
            Vector2f dir(cos(angle), sin(angle));

            float closestDist = numeric_limits<float>::max();
            Vector2f closestPoint;

            for (const auto& wall : walls) {
                Vector2f intersection;
                if (getIntersection(sourcePosition, dir, wall.a, wall.b, intersection)) {
                    float dist = hypot(intersection.x - sourcePosition.x, intersection.y - sourcePosition.y);
                    if (dist < closestDist) {
                        closestDist = dist;
                        closestPoint = intersection;
                    }
                }
            }

            if (closestDist < numeric_limits<float>::max()) {
                VertexArray ray(Lines, 2);
                ray[0].position = sourcePosition;
                ray[0].color = Color::Yellow;
                ray[1].position = closestPoint;
                ray[1].color = Color::White;
                beams.push_back(ray);
            }
        }
    }

    void draw(RenderWindow& window) {
        for (auto& beam : beams) {
            window.draw(beam);
        }
    }
};

// ---------------------------- Main ----------------------------
int main() {
    RenderWindow window(VideoMode(800, 800), "Raycasting with Walls", Style::Close);
    window.setFramerateLimit(60);

    Torch source;
    Beam beam;

    vector<Wall> walls;
    // Add some random walls
    walls.emplace_back(Vector2f(100, 100), Vector2f(300, 150));
    walls.emplace_back(Vector2f(400, 400), Vector2f(600, 500));
    walls.emplace_back(Vector2f(700, 100), Vector2f(750, 300));
    walls.emplace_back(Vector2f(200, 600), Vector2f(600, 700));
    walls.emplace_back(Vector2f(0, 0), Vector2f(800, 0));
    walls.emplace_back(Vector2f(800, 0), Vector2f(800, 800));
    walls.emplace_back(Vector2f(800, 800), Vector2f(0, 800));
    walls.emplace_back(Vector2f(0, 800), Vector2f(0, 0)); // borders

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        source.update(window);
        beam.update(source.getPosition(), walls);

        beam.draw(window);
        for (auto& wall : walls)
            wall.draw(window);
        source.draw(window);

        window.display();
    }

    return 0;
}
