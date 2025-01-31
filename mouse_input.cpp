#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
    player.setFillColor(sf::Color::Green);
    sf::Vector2f size = player.getSize();
    player.setOrigin(size.x/2,size.y/2); //if commented, you'll see that the top left corner of the rectangle moves to the point clicked, not the center, so used this
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
                case evnt.Resized:
                    std::cout<<evnt.size.height<<" "<<evnt.size.width<<'\n';
                    break;
                case evnt.TextEntered:
                    if(evnt.text.unicode < 128)
                std::cout<<static_cast<char>(evnt.text.unicode)<<"";
                break;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos= sf::Mouse::getPosition(window); //return the position to the screen and not to the window, because mouse position is with respect to the screen and not the window
            player.setPosition(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)); //you can use C type casting: (float)mousePos.x, but don't ever use it for classes, instead use the static cast function
        }
                window.clear();//just try sf::Color::Blue or any other color 
        window.draw(player);
        window.display(); //Simple games use double buffering, first draw to the backbuffer and then swap with the front buffer (front becomes back), now draw to the back buffer and and so on for each frame, AAA games use triple buffering, that is out of scope
    }
    return 0;
}
