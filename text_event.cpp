#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
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
    }
    return 0;
}
