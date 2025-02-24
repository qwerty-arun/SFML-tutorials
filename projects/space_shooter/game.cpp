#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>

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

    /*sf::Texture backgroundTexture;*/
    /*if (!backgroundTexture.loadFromFile("/home/jarvis/work/SFML-tutorials/projects/space_shooter/space_background.jpeg")) {*/
    /*    std::cout<< "Failed to load background image!" << std::endl;*/
    /*    return -1; // Exit if loading fails*/
    /*}*/
    /**/
    /*// Create sprite and set the texture*/
    /*sf::Sprite backgroundSprite;*/
    /*backgroundSprite.setTexture(backgroundTexture);*/
    /**/
    /*// Scale the image to fit the window (Optional)*/
    /*sf::Vector2u windowSize = window.getSize();*/
    /*sf::Vector2u textureSize = backgroundTexture.getSize();*/
    /*float scaleX = static_cast<float>(windowSize.x) / textureSize.x;*/
    /*float scaleY = static_cast<float>(windowSize.y) / textureSize.y;*/
    /*backgroundSprite.setScale(scaleX, scaleY);*/
    // create an empty shape
/*sf::ConvexShape convex;*/
/**/
/*// resize it to 5 points*/
/*convex.setPointCount(5);*/
/**/
/*// define the points*/
/*convex.setPoint(0, {0.f, 0.f});*/
/*convex.setPoint(1, {150.f, 10.f});*/
/*convex.setPoint(2, {120.f, 90.f});*/
/*convex.setPoint(3, {30.f, 100.f});*/
/*convex.setPoint(4, {0.f, 50.f});*/
/*    convex.setFillColor(sf::Color::Blue);*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
	sf::Vector2f position = ship.getPosition();
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
                    ship.setFillColor(sf::Color(rand()%256,rand()%256,rand()%256));
                    //bullet code
            }
        window.clear(sf::Color::Black);
	window.draw(ship);
	/*window.draw(convex);*/
        window.display();
    }
    return 0;
}
