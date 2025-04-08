#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(800, 600), "Planetary Motion");
    window.setFramerateLimit(60);

    CircleShape sun{35};
    sun.setFillColor(Color::Yellow);
    sun.setOrigin(35, 35);
    sun.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    CircleShape earth{15};
    earth.setFillColor(Color::Blue);
    earth.setOrigin(15, 15);

    CircleShape moon{5};
    moon.setFillColor(Color::White);
    moon.setOrigin(5, 5);

    Clock clock;
    float angle = 0.f;
    float orbitRadius = 150.f;  // Distance from the sun
    float orbitSpeed = 50.f;    // degrees per second
    //
    //Moon
    float Mradius = 40.f;
    float Mspeed = 180.f; 
    float Mangle = 0.f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }

        // Update
        float deltaTime = clock.restart().asSeconds();
        angle += orbitSpeed * deltaTime; // increment angle
        Mangle += Mspeed* deltaTime; // increment angle

        // Compute new earth position
        earth.setPosition(
            sun.getPosition().x + orbitRadius * std::cos(angle * 3.14159265 / 180.f),
            sun.getPosition().y + orbitRadius * std::sin(angle * 3.14159265 / 180.f)
        );

        moon.setPosition(
            earth.getPosition().x + Mradius * std::cos(Mangle * 3.14159265 / 180.f),
            earth.getPosition().y + Mradius* std::sin(Mangle * 3.14159265 / 180.f)
        );


        // Draw
        window.clear();
        window.draw(sun);
        window.draw(earth);
        window.draw(moon);
        window.display();
    }

    return 0;
}

