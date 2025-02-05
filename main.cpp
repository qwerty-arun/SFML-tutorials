#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512),"Arun's first trial",sf::Style::Resize|sf::Style::Close);
    window.setFramerateLimit(60);
    sf::CircleShape shape(50.0f,3);
    shape.setFillColor(sf::Color(150, 50, 250));

// set a 10-pixel wide orange outline
shape.setOutlineThickness(10.f);
shape.setOutlineColor(sf::Color(250, 150, 100));
    shape.setPosition(sf::Vector2f(100.f,100.f));
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
        window.draw(shape);
        window.display();
    }
    return 0;
}
