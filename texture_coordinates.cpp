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
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
    sf::RectangleShape player(sf::Vector2f(150.0f,150.0f)); //f stands for float here, never use Vector2 because we need to specify the types
    /*player.setFillColor(sf::Color::Green);*/
    player.setPosition(206.0f,206.0f);
    sf::Texture playerTexture; //defining a texture
    playerTexture.loadFromFile("diff_imposters.png"); // there are 12 diff imposters 4x3 
    player.setTexture(&playerTexture); 
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x/=3; //three columns, note that this is the width of one imposter
    textureSize.y/=4; //four rows, height of one imposter

    //now we need to select the imposter what I want: the bottom right one (red with chef hat)
        player.setTextureRect(sf::IntRect(textureSize.x * 2,  textureSize.y * 3,textureSize.x,textureSize.y)); //2 and 3 are just offsets, last two parameters are just height and width of one imposter
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
