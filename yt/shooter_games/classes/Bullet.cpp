#include "Bullet.h"

    CircleShape shape;
    Vector2f velocity;
    float speed;

Bullet::Bullet(Vector2f pos, Vector2f dir) {
        shape.setRadius(5.f);
        shape.setFillColor(Color::Red);
        shape.setPosition(pos);
        speed = 15.f;
        velocity = dir * speed;
    }

    void Bullet::update() {
        shape.move(velocity);
    }
