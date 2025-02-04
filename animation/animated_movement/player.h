#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "animation.h"
class Player
{
	public:
		Player(sf::Texture* texture, sf::Vector2u ImageCount, float swithTime,float speed);
		~Player();
		
		void Update(float deltaTime);	
		void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};
