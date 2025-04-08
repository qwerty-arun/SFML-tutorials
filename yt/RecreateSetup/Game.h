# pragma once

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
#include <vector>

class Game
{
private:
	//variables
	sf::RenderWindow* window;
	sf::Event ev;

	sf::CircleShape enemy;
	int enemySpawnTimer;
	std::vector<sf::CircleShape> enemies;

	//functions
	void initVariables();
	void initWindow();

public:
	//constructors and destructors
	Game();
	virtual ~Game();	

	//Accessors
	const bool running() const;
	//functions
	void pollEvents();
	void update();
	void render();
};
