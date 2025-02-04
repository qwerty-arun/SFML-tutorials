#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "animation.h"
#include <ctime>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
    sf::RectangleShape player(sf::Vector2f(150.0f,150.0f)); //f stands for float here, never use Vector2 because we need to specify the types
    /*player.setFillColor(sf::Color::Green);*/
    player.setPosition(206.0f,206.0f);
    sf::Texture playerTexture; //defining a texture
    playerTexture.loadFromFile("../images/diff_imposters.png"); // there are 12 diff imposters 4x3 
    player.setTexture(&playerTexture); 

    Animation animation(&playerTexture,sf::Vector2u(3,4),0.3f);
    float deltaTime = 0.0f;
    sf::Clock clock;
    while(window.isOpen())
    {
        deltaTime=clock.restart().asSeconds();
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case evnt.Closed:
                    window.close();
                    break;
            }
        }

        animation.Update(0,deltaTime);
        player.setTextureRect(animation.uvRect);
        window.clear(sf::Color(150,150,150));
        window.draw(player);
        window.display();
    }
    return 0;
}
