# pragma once
# include <SFML/Graphics.hpp>
# include <cmath>
// ---------- Enemy Class ---------
using namespace sf;
class Enemy {
public:
	//variables
    RectangleShape shape;
    float speed;

	//functions
    Enemy(Vector2f pos); 
    void update(Vector2f playerPos); 
};

