#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
    sf::RectangleShape player(sf::Vector2f(100.0f,100.0f)); //f stands for float here, never use Vector2 because we need to specify the types
    /*player.setFillColor(sf::Color::Green);*/
    player.setPosition(206.0f,206.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("amongus.png");
    player.setTexture(&playerTexture);
    // If you DO want to put it somewhere else, in a sub-floder called textures for instance, then you will have to type the folder name plus a SLASH before the texture name. I fyou texture is a folder up, then you will have to type ../ for each folder that you need to go up.
    // ../texture_name.png if your texture is a folder up
    // folder/texture_name.png if your ttexture is a folder down.
    while(window.isOpen())
    {
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
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
