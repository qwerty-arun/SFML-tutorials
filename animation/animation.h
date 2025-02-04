#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //we are only using the texture and not storing it becoz we don't care about texture itself we only care about size. 
	//Why aren't we passing sizes then? The constructor call will be big
	~Animation();

	void Update(int row, float deltaTime); //deltatime is the time diff between the current frame and the previous frame, we do this to make sure the program runs the same on all computer
	//on high end gaming laptops, it will run fast(0.1 sec) and old laptops it my even be 10sec, so the above variable solves, even though on old computers it may not be as smooth

public: //keeping variables and functions seperate becoz in huge classes it will be a mess
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount; //this never going to be less than zero, therefore unsigned
	sf::Vector2u currentImage;
	// if you are trying to access image that is outside of the current image: you can clamp it or you can have texture repeat
	// you can enable texture repeat.setrepeated(bool) and smooth filter by calling setsmooth(bool), this will make the pixels less noticable
	float totalTime;
	float switchTime;
};
