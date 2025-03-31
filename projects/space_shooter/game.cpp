#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace sf;

int main() {
    // Create window
    RenderWindow window(VideoMode(800, 600), "Asteroid Game", Style::Close | Style::Resize);
    Clock clock;
    
    //Sound Effects
    SoundBuffer buffer;
    if(!buffer.loadFromFile("laser_gun.wav"))
        return -1;

    Sound shoot(buffer);
    shoot.setPitch(1.5f);


    // Load ship texture
    Texture shipTexture;
    if (!shipTexture.loadFromFile("spaceship.jpeg")) {
        std::cerr << "Error: Could not load spaceship.jpeg" << std::endl;
        return -1;
    }

    // Ship settings
    RectangleShape ship(Vector2f(55, 55));
    ship.setTexture(&shipTexture);
    ship.setOrigin(27.5f, 27.5f);  // Centered origin
    ship.setPosition(400, 500);
    ship.setRotation(0);

    Texture asteroidTexture;
    if(!asteroidTexture.loadFromFile("asteroid.png"))
    {
        std::cerr << "Error: Could not load laserbeam.png" << std::endl;
        return -1;
    }
    Sprite asteroid;
    asteroid.setTexture(asteroidTexture);

    asteroid.setScale(0.3f,0.3f);
    /*asteroid.setPosition(100.f,100.f);*/
    // Load bullet texture
    Texture bulletTexture;
    if (!bulletTexture.loadFromFile("laserbeam.png")) {
        std::cerr << "Error: Could not load laserbeam.png" << std::endl;
        return -1;
    }

    struct Bullet {
        Sprite sprite;
        Vector2f velocity;
    };

    std::vector<Bullet> bullets;
    int shootTimer = 0;

    // Asteroids
    std::vector<Sprite> asteroids;
    int asteroidTimer = 0;

    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        Vector2f shipPos = ship.getPosition();
        float shipRotation = ship.getRotation() - 90;
        float rotationRadians = shipRotation * (3.14159265f / 180.0f);

        // Ship Movement
        if (Keyboard::isKeyPressed(Keyboard::A)) ship.move(-5.5f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::D)) ship.move(5.5f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::W)) ship.move(0.0f, -5.5f);
        if (Keyboard::isKeyPressed(Keyboard::S)) ship.move(0.0f, 5.5f);
        if (Keyboard::isKeyPressed(Keyboard::J)) ship.rotate(-5.f);
        if (Keyboard::isKeyPressed(Keyboard::K)) ship.rotate(5.f);

        // Screen Wrapping
        if (shipPos.x > window.getSize().x) ship.setPosition(0, shipPos.y);
        if (shipPos.x < 0) ship.setPosition(window.getSize().x, shipPos.y);
        if (shipPos.y > window.getSize().y) ship.setPosition(shipPos.x, 0);
        if (shipPos.y < 0) ship.setPosition(shipPos.x, window.getSize().y);

        // Shooting bullets
        if (shootTimer < 5) shootTimer++;
        if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 5) {
            shoot.play();
            Bullet newBullet;
            newBullet.sprite.setTexture(bulletTexture);
            newBullet.sprite.setScale(0.1f, 0.5f);
            newBullet.sprite.setRotation(shipRotation);
            newBullet.sprite.setPosition(shipPos.x-12,shipPos.y);
            newBullet.velocity = Vector2f(10 * cos(rotationRadians), 10 * sin(rotationRadians));
            bullets.push_back(newBullet);
            shootTimer = 0;
        }

        // Move bullets
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].sprite.move(bullets[i].velocity);

            // Delete bullets when they leave the screen
            Vector2f bulletPos = bullets[i].sprite.getPosition();
            if (bulletPos.x < 0 || bulletPos.x > window.getSize().x || bulletPos.y < 0 || bulletPos.y > window.getSize().y) {
                bullets.erase(bullets.begin() + i);
            }
        }

        // Spawn asteroids
        if (asteroidTimer < 50) asteroidTimer++;
        if (asteroidTimer >= 50) {
            /*RectangleShape newAsteroid(Vector2f(50.f, 50.f));*/
            /*newAsteroid.setFillColor(Color::White);*/
            asteroid.setOrigin(20.f,20.f);
            asteroid.setPosition(rand() % int(window.getSize().x -50), 0.f);
            /*asteroid.setPosition(rand() % int(window.getSize().x -50), rand() % int(window.getSize().y));*/
            asteroids.push_back(Sprite(asteroid));
            asteroidTimer = 0;
        }

        // Move asteroids
        for (size_t i = 0; i < asteroids.size(); i++) {
            asteroids[i].rotate(2.f);
            asteroids[i].move(0.f, 5.f);
            if (asteroids[i].getPosition().y > window.getSize().y) {
                asteroids.erase(asteroids.begin() + i);
            }
        }

        // Collision Detection (Bullets & Asteroids)
        for (int i = bullets.size() - 1; i >= 0; --i) {
            for (int j = asteroids.size() - 1; j >= 0; --j) {
                if (bullets[i].sprite.getGlobalBounds().intersects(asteroids[j].getGlobalBounds())) {
                    bullets.erase(bullets.begin() + i);
                    asteroids.erase(asteroids.begin() + j);
                    break;
                }
            }
        }

        // Render objects
        window.clear(Color::Black);
        for (const auto& asteroid : asteroids) window.draw(asteroid);
        for (const auto& bullet : bullets) window.draw(bullet.sprite);
        window.draw(ship);
        window.display();
    }

    return 0;
}
