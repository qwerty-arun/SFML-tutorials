#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
class Player
{
	private:
		Texture *texture;
		Sprite shape;
		RectangleShape hitBox;
		int level;
		int exp;
		int expNext;
		int hp;
		int hpMax;
		int score;
		int damage;
public:
	Player();
	virtual ~Player();
	void Update();
	void Draw();
};
