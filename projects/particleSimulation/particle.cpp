#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cmath>

const float GRAVITY = 500.0f; // Gravity strength
const float PARTICLE_RADIUS = 10.0f;
const float RESTITUTION = 0.8f; // Elasticity of collision
const float DAMPING = 0.9f;
// Particle Class
class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::Color color;

    Particle(float x, float y)
        : position(x, y), velocity(0, 0), radius(PARTICLE_RADIUS) {
        color = sf::Color::White;
    }

    void update(float deltaTime) {
        velocity.y += GRAVITY * deltaTime; // Apply gravity
        position += velocity * deltaTime;  // Update position
    }

    void checkWallCollision(sf::RenderWindow& window) {
        sf::Vector2u winSize = window.getSize();

        // Bounce off left and right walls
        if (position.x - radius < 0) {
            position.x = radius;
            velocity.x = -velocity.x * RESTITUTION;
        } 
        else if (position.x + radius > winSize.x) {
            position.x = winSize.x - radius;
            velocity.x = -velocity.x * RESTITUTION;
        }

        // Bounce off the floor
        if (position.y + radius > winSize.y) {
            position.y = winSize.y - radius;
            velocity.y = -velocity.y * RESTITUTION;
        }
        if(position.y - radius <0)
        {
            position.y = radius;
            velocity.y = -velocity.y * RESTITUTION;
        }
    }
};

// Detects and resolves collisions between two particles
void handleParticleCollision(Particle& p1, Particle& p2) {
    sf::Vector2f delta = p2.position - p1.position;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float minDist = p1.radius + p2.radius;

    if (dist < minDist && dist > 0.0f) {
        // Normalize delta
        sf::Vector2f normal = delta / dist;
        sf::Vector2f relativeVelocity = p2.velocity - p1.velocity;

        // Compute relative velocity along the normal
        float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        // If moving away, do nothing
        if (velocityAlongNormal > 0) return;

        // Elastic collision response
        float j = -(1 + RESTITUTION) * velocityAlongNormal * DAMPING;
        sf::Vector2f impulse = j * normal;

        p1.velocity -= impulse;
        p2.velocity += impulse;

        // Resolve overlap
        float overlap = (minDist - dist) / 2.0f;
        p1.position -= normal * overlap;
        p2.position += normal * overlap;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Collision");
    std::vector<Particle> particles;
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Create particle on left-click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                particles.emplace_back(mousePos.x, mousePos.y);
            }
        }

        // Update all particles
        for (auto& particle : particles) {
            particle.update(deltaTime);
            particle.checkWallCollision(window);
        }

        // Handle particle collisions
        for (size_t i = 0; i < particles.size(); i++) {
            for (size_t j = i + 1; j < particles.size(); j++) {
                handleParticleCollision(particles[i], particles[j]);
            }
        }

        // Draw everything
        window.clear();
        for (auto& particle : particles) {
            sf::CircleShape shape(particle.radius);
            shape.setFillColor(particle.color);
            shape.setPosition(particle.position - sf::Vector2f(particle.radius, particle.radius));
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}

