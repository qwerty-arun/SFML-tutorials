#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace sf;

// ---------- Bullet Class ----------
class Bullet {
public:
    CircleShape shape;
    Vector2f velocity;
    float speed;

    Bullet(Vector2f pos, Vector2f dir) {
        shape.setRadius(5.f);
        shape.setFillColor(Color::Red);
        shape.setPosition(pos);
        speed = 15.f;
        velocity = dir * speed;
    }

    void update() {
        shape.move(velocity);
    }
};

// ---------- Enemy Class ----------
class Enemy {
public:
    RectangleShape shape;
    float speed;

    Enemy(Vector2f pos) {
        shape.setSize(Vector2f(50.f, 50.f));
        shape.setFillColor(Color::Magenta);
        shape.setPosition(pos);
        speed = 1.f + static_cast<float>(rand() % 3); // random speed 1-3
    }

    void update(Vector2f playerPos) {
        Vector2f dir = playerPos - shape.getPosition();
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
            dir /= len;
        shape.move(dir * speed);
    }
};

// ---------- Normalize Function ----------
Vector2f normalize(Vector2f v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0)
        return v / length;
    return v;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(800, 600), "2D Shooter Game");
    window.setFramerateLimit(60);

    // Player
    CircleShape player(25);
    player.setFillColor(Color::White);
    player.setPosition(400.f, 300.f);
    float playerSpeed = 8.f;

    // Bullets and Enemies
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    int spawnTimer = 0;
    int score = 0;

    // Font & Text
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Missing font file!" << std::endl;
        return -1;
    }
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10.f, 10.f);

    // ---------- Game Loop ----------
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }

        // ----------- Player Movement -----------
        if (Keyboard::isKeyPressed(Keyboard::W)) player.move(0, -playerSpeed);
        if (Keyboard::isKeyPressed(Keyboard::S)) player.move(0, playerSpeed);
        if (Keyboard::isKeyPressed(Keyboard::A)) player.move(-playerSpeed, 0);
        if (Keyboard::isKeyPressed(Keyboard::D)) player.move(playerSpeed, 0);

        // ----------- Shoot Bullet -----------
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2f playerCenter = player.getPosition() + Vector2f(player.getRadius(), player.getRadius());
            Vector2f aimDir = normalize(Vector2f(Mouse::getPosition(window)) - playerCenter);
            bullets.push_back(Bullet(playerCenter, aimDir));
        }

        // ----------- Spawn Enemies -----------
        if (spawnTimer < 30)
            spawnTimer++;
        else {
            Vector2f spawnPos(rand() % (window.getSize().x - 50), rand() % (window.getSize().y - 50));
            enemies.push_back(Enemy(spawnPos));
            spawnTimer = 0;
        }

        // ----------- Update Bullets -----------
        for (size_t i = 0; i < bullets.size();) {
            bullets[i].update();
            if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x ||
                bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y) {
                bullets.erase(bullets.begin() + i);
            } else {
                i++;
            }
        }

        // ----------- Update Enemies -----------
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(player.getPosition());
        }

        // ----------- Bullet-Enemy Collision -----------
        for (size_t i = 0; i < bullets.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++) {
                if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds())) {
                    bullets.erase(bullets.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    score++;
                    i--; // important to prevent skipping bullets
                    break;
                }
            }
        }

        // ----------- Draw -----------
        window.clear();

        window.draw(player);

        for (auto& b : bullets) window.draw(b.shape);
        for (auto& e : enemies) window.draw(e.shape);

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
