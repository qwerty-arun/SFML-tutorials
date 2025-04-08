# pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <ctime>

/*
 Class that acts as the game engine
 Wrapper Class
*/

class Game
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game Logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemy();

	void updateMousePositions();
	void pollEvents();

	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};
