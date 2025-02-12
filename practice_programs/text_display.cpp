#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500,500),"Rewrite yet again",sf::Style::Resize|sf::Style::Close);
    sf::RectangleShape rect(sf::Vector2f(20.f,20.f));
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(250.0f,250.0f);
    sf::Vector2f velocity(2.0f,2.0f); //speed in x and y directions
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cerr <<"Error loading file\n";
        return -1;
    }
        sf::Text text;
    text.setFont(font);
    text.setString("Hello, SFML!");
    text.setCharacterSize(30);      // Font size
    text.setFillColor(sf::Color::White);  // Text color
    text.setPosition(150, 200);
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == sf::Event::Closed)
                window.close();
        }
        rect.move(velocity);
        if(rect.getPosition().x <=0 || rect.getPosition().x+40>=500)
            velocity.x = -velocity.x;
        if(rect.getPosition().y <=0 || rect.getPosition().y+40>=500)
            velocity.y = -velocity.y;
    window.clear();
    window.draw(text);
    window.display();
    }
    return 0;
}
