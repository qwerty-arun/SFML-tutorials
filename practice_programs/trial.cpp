#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

struct object{
    sf::RectangleShape rect;
    float mass;
    sf::Vector2f velocity;
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(500,500),"Rewrite yet again",sf::Style::Resize|sf::Style::Close);

    object rec1,rec2;
    rec1.rect.setFillColor(sf::Color::Yellow);
    rec1.rect.setPosition(100.f,250.f);
    rec1.rect.setSize(sf::Vector2f(50.f,50.f));
    rec1.mass = 2.0;
    rec1.velocity = sf::Vector2f(2.2f,2.0f); //speed in x and y directions

    rec2.rect.setFillColor(sf::Color::Red);
    rec2.rect.setPosition(350.f,250.f);
    rec2.rect.setSize(sf::Vector2f(50.f,50.f));
    rec2.mass = 2.0;
    rec2.velocity = sf::Vector2f(-1.0f,2.0f); //speed in x and y directions

    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cerr <<"Error loading file\n";
        return -1;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Collision Detection");
    text.setCharacterSize(30);      // Font size
    text.setFillColor(sf::Color::Green);  // Text color
    text.setPosition(0, 0);
    text.setStyle(sf::Text::Bold|sf::Text::Italic);
    int no_of_collisions{0};
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == sf::Event::Closed)
                window.close();
        }
        rec1.rect.move(rec1.velocity);
        rec2.rect.move(rec2.velocity);
        if(rec1.rect.getGlobalBounds().intersects(rec2.rect.getGlobalBounds()))
        {
            rec1.velocity.x = -rec1.velocity.x;
            rec2.velocity.x = -rec2.velocity.x;
        }
        if(rec2.rect.getPosition().x+50>=500 || rec2.rect.getPosition().x<=0)
            rec2.velocity.x = -rec2.velocity.x;

        if(rec1.rect.getPosition().x+50>=500 || rec1.rect.getPosition().x<=0)
            rec1.velocity.x = -rec1.velocity.x;

        if(rec2.rect.getPosition().y+50>=500 || rec2.rect.getPosition().x<=0)
        {
            rec2.velocity.y = -rec2.velocity.y;
        }
        if(rec1.rect.getPosition().y+50>=500 || rec1.rect.getPosition().y<=0)
        {
            rec1.velocity.y = -rec1.velocity.y;
        }
    window.clear();
    window.draw(text);
    window.draw(rec1.rect);
    window.draw(rec2.rect);
    window.display();
    }
    return 0;
}
