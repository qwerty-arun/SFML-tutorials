#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Player class
class Player {
public:
    sf::RectangleShape rect;
    sf::Vector2f velocity;
    bool onGround;

    Player(sf::Vector2f position) {
        rect.setSize(sf::Vector2f(32, 64));
        rect.setFillColor(sf::Color::Green);
        rect.setPosition(position);
        velocity = sf::Vector2f(0, 0);
        onGround = false;
    }

    void update(float deltaTime) {
        // Apply gravity
        if (!onGround) {
            velocity.y += 981.0f * deltaTime; // 981 pixels per second squared
        } else {
            velocity.y = 0;
        }

        // Update position
        rect.move(velocity * deltaTime);
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -200.0f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = 200.0f;
        } else {
            velocity.x = 0;
        }

        // Jump if on ground
        if (onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            velocity.y = -400.0f;
            onGround = false;
        }
    }
};

// Platform class
class Platform {
public:
    sf::RectangleShape rect;

    Platform(sf::Vector2f position, sf::Vector2f size) {
        rect.setSize(size);
        rect.setFillColor(sf::Color::White);
        rect.setPosition(position);
    }
};

// Check collision between player and platform
bool checkCollision(const Player& player, const Platform& platform) {
    return player.rect.getGlobalBounds().intersects(platform.rect.getGlobalBounds());
}

// Handle collision resolution
void handleCollision(Player& player, const Platform& platform) {
    sf::FloatRect playerBounds = player.rect.getGlobalBounds();
    sf::FloatRect platformBounds = platform.rect.getGlobalBounds();

    // Calculate overlap in all directions
    float overlapLeft = playerBounds.left + playerBounds.width - platformBounds.left;
    float overlapRight = platformBounds.left + platformBounds.width - playerBounds.left;
    float overlapTop = playerBounds.top + playerBounds.height - platformBounds.top;
    float overlapBottom = platformBounds.top + platformBounds.height - playerBounds.top;

    // Find the smallest overlap
    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;

    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;

    // Resolve collision along the axis of least penetration
    if (minOverlapX < minOverlapY) {
        if (fromLeft) {
            player.rect.setPosition(platformBounds.left - playerBounds.width, playerBounds.top);
        } else {
            player.rect.setPosition(platformBounds.left + platformBounds.width, playerBounds.top);
        }
        player.velocity.x = 0;
    } else {
        if (fromTop) {
            player.rect.setPosition(playerBounds.left, platformBounds.top - playerBounds.height);
            player.onGround = true;
        } else {
            player.rect.setPosition(playerBounds.left, platformBounds.top + platformBounds.height);
        }
        player.velocity.y = 0;
    }
}

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Platformer");
    window.setFramerateLimit(60);

    // Create clock for delta time
    sf::Clock clock;

    // Create player
    Player player(sf::Vector2f(100, 100));

    // Create platforms
    std::vector<Platform> platforms;
    platforms.emplace_back(sf::Vector2f(0, 550), sf::Vector2f(800, 50)); // Ground
    platforms.emplace_back(sf::Vector2f(100, 450), sf::Vector2f(100, 20));
    platforms.emplace_back(sf::Vector2f(300, 400), sf::Vector2f(100, 20));
    platforms.emplace_back(sf::Vector2f(500, 350), sf::Vector2f(100, 20));
    platforms.emplace_back(sf::Vector2f(200, 300), sf::Vector2f(100, 20));

    // Game loop
    while (window.isOpen()) {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update player
        player.handleInput();
        player.update(deltaTime);
        player.onGround = false; // Reset ground state - will be set to true if collision occurs

        // Check collisions with all platforms
        for (auto& platform : platforms) {
            if (checkCollision(player, platform)) {
                handleCollision(player, platform);
            }
        }

        // Keep player in bounds
        if (player.rect.getPosition().x < 0) {
            player.rect.setPosition(0, player.rect.getPosition().y);
        }
        if (player.rect.getPosition().x > window.getSize().x - player.rect.getSize().x) {
            player.rect.setPosition(window.getSize().x - player.rect.getSize().x, player.rect.getPosition().y);
        }

        // Drawing
        window.clear(sf::Color::Black);

        // Draw platforms
        for (auto& platform : platforms) {
            window.draw(platform.rect);
        }

        // Draw player
        window.draw(player.rect);

        window.display();
    }

    return 0;
}
