#include "Enemy.h"
#include <SFML/Graphics.hpp>

    Enemy::Enemy(Vector2f pos) {
        shape.setSize(Vector2f(50.f, 50.f));
        shape.setFillColor(Color::Magenta);
        shape.setPosition(pos);
        speed = 1.f + static_cast<float>(rand() % 3); // random speed 1-3
    }

    void Enemy::update(Vector2f playerPos) {
        Vector2f dir = playerPos - shape.getPosition();
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
            dir /= len;
        shape.move(dir * speed);
    }

