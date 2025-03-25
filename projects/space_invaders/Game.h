#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"

using namespace sf;
class Game
{
private:
	RenderWindow *window;

public:
	Game(RenderWindow *window);
	virtual ~Game();

	//Accessors
	inline RenderWindow& getWindow(){
		return *this->window;
	}
	
	//Setters
	
	//Functions
	void Update();

	void Draw();
};
