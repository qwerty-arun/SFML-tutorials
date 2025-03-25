#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>

void drawBullet(sf::RenderWindow *window,sf::RectangleShape* bullet, sf::Vector2f position)
{
                    bullet->setFillColor(sf::Color::Red);
                    bullet->setPosition(position);
                    bullet->setSize(sf::Vector2f(10.0f,10.0f));
                        window->draw(*bullet);
}
int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Asteroid game",sf::Style::Resize|sf::Style::Close);
    sf::CircleShape ship(35,3);
    sf::Clock clock;

    sf::Texture shipTexture;
    shipTexture.loadFromFile("/home/jarvis/work/SFML-tutorials/projects/space_shooter/spaceship.jpeg");
    ship.setTexture(&shipTexture);
    shipTexture.setSmooth(true);
    ship.setOrigin(35,35);
    ship.setPosition(100,100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
	sf::Vector2f position = ship.getPosition();
        sf::RectangleShape bullet;
        //boundary conditions, getting back the ship into the frame
        if(position.x >=500)
        {
            ship.setPosition(0,position.y);
        }
        if(position.x<=0.0)
        {
            ship.setPosition(500,position.y);
        }
        if(position.y >=500)
        {
            ship.setPosition(position.x,0);
        }
        if(position.y<=0.0)
        {
            ship.setPosition(position.x,500);
        }

        //keyboard input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                    ship.move(-2.5f,0.0f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                    ship.move(2.5f,0.0f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                    ship.move(0.0f,-2.5f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                    ship.move(0.0f,2.5f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
            {
                    ship.rotate(-deltaTime*200.f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
            {
                    ship.rotate(deltaTime*200.f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                    //random color for now
                    /*ship.setFillColor(sf::Color(rand()%256,rand()%256,rand()%256));*/
                    sf::Vector2f spacecraft_position = ship.getPosition();
                    bullet.setFillColor(sf::Color::Red);
                    bullet.setPosition(position);
                    bullet.setSize(sf::Vector2f(3.0f,3.0f));
                    /*drawBullet(&window, &bullet, spacecraft_position);*/
            }
        bullet.move(sf::Vector2f(2.0f,2.0f));
        window.clear(sf::Color::Black);
	window.draw(ship);
	window.draw(bullet);
	/*window.draw(convex);*/
        window.display();
    }
    return 0;
}
