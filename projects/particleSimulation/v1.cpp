#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>  // for rand()
// Constants
const float GRAVITY = 500.0f;  // Strength of gravity
const float BOUNCE_DAMPENING = 0.7f;  // Energy loss on collision
const int PARTICLE_COUNT = 100;

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius;
    sf::Color color;

    Particle(float x, float y, float r, sf::Color c) 
        : position(x, y), radius(r), color(c), velocity(0, 0), acceleration(0, 0) {}

    void applyForce(sf::Vector2f force) {
        acceleration += force;
    }

    void update(float dt, sf::RenderWindow& window) {
        velocity += acceleration * dt;
        position += velocity * dt;

        // Collision with window boundaries
        if (position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -BOUNCE_DAMPENING;
        }
        if (position.x + radius > window.getSize().x) {
            position.x = window.getSize().x - radius;
            velocity.x *= -BOUNCE_DAMPENING;
        }
        if (position.y - radius < 0) {
            position.y = radius;
            velocity.y *= -BOUNCE_DAMPENING;
        }
        if (position.y + radius > window.getSize().y) {
            position.y = window.getSize().y - radius;
            velocity.y *= -BOUNCE_DAMPENING;
        }

        acceleration=sf::Vector2f(0,0); // Reset acceleration each frame
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape shape(radius);
        shape.setPosition(position.x - radius, position.y - radius);
        shape.setFillColor(color);
        window.draw(shape);
    }
};

std::vector<Particle> particles;

void initParticles() {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        float x = rand() % 800;
        float y = rand() % 600;
        float r = 5 + rand() % 10;
        sf::Color c(rand() % 255, rand() % 255, rand() % 255);
        particles.emplace_back(x, y, r, c);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulation");
    window.setFramerateLimit(60);
    
    initParticles();
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds(); // Time step

        // Apply gravity and update particles
        for (auto& p : particles) {
            p.applyForce(sf::Vector2f(0, GRAVITY));
            p.update(dt, window);
        }

        window.clear();
        for (auto& p : particles) {
            p.draw(window);
        }
        window.display();
    }

    return 0;
}

