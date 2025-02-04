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
/*#include "animation.h"*/
# include "player.h"
#include <ctime>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
    /*player.setFillColor(sf::Color::Green);*/
    sf::Texture playerTexture; //defining a texture
    playerTexture.loadFromFile("amongus_sprites.png"); // there are 12 diff imposters 4x3 

    Player player(&playerTexture,sf::Vector2u(3,4),0.3f,100.0f);
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

        player.Update(deltaTime);
        window.clear(sf::Color(150,150,150));
        player.Draw(window);
        window.display();
    }
    return 0;
}
