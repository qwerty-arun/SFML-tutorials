#include "animation.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    //this is a pointer to the class itself
    this->imageCount=imageCount; //the left one is the private variable and right side is the parameter, note the colors are also different
    this->switchTime=switchTime;
    totalTime=0.0f;
    currentImage.x=0;
    uvRect.width=texture->getSize().x /float(imageCount.x);
    uvRect.height=texture->getSize().y /float(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime)
{
    currentImage.y=row;
    totalTime +=deltaTime;
    if(totalTime>=switchTime)
    {
        totalTime-=switchTime;
        currentImage.x++;
        if(currentImage.x >=imageCount.x)
        {
            currentImage.x=0; //extremely important, this is the clamping effect
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top= currentImage.y * uvRect.height;
}
