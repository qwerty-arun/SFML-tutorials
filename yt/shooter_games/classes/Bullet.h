# pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet {
public:
    CircleShape shape;
    Vector2f velocity;
    float speed;

    Bullet(Vector2f pos, Vector2f dir);

    void update();
};
