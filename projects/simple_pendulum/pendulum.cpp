#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159f;

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Pendulum Simulation");

    // **Pendulum Parameters**
    float length = 150.f;         // Length of the pendulum rod
    float angle = 45.f;           // Initial angle (from vertical)
    float angularVelocity = 0.f;  // Initial velocity
    float angularAcceleration = 0.f;
    float gravity = 0.4f;         // Simulated gravity

    // **Pivot Point (Fixed)**
    sf::Vector2f pivot(250.f, 100.f);

    // **Rod (Pendulum Arm)**
    sf::RectangleShape rod(sf::Vector2f(5.f, length));  // Set the rod to be a **vertical rectangle**
    rod.setOrigin(2.5f, 0.f);  // Set origin to **top center** so it rotates from pivot
    rod.setPosition(pivot);
    rod.setFillColor(sf::Color::White);

    // **Bob (Mass at End of the Pendulum)**
    sf::CircleShape bob(15.f);
    bob.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // **Pendulum Physics (θ'' = -g/L * sin(θ))**
        angularAcceleration = (-gravity / length) * sin(angle * PI / 180.f);
        angularVelocity += angularAcceleration;
        angle += angularVelocity;

        // **Calculate the new position of the pendulum bob**
        float x = pivot.x + length * sin(angle * PI / 180.f);
        float y = pivot.y + length * cos(angle * PI / 180.f);
        bob.setPosition(x - bob.getRadius(), y - bob.getRadius());

        // **Update the rod's rotation to match the pendulum motion**
        rod.setRotation(-angle);

        // **Render Everything**
        window.clear();
        window.draw(rod);
        window.draw(bob);
        window.display();
    }

    return 0;
}

