// Simple Shoot the target game with mouse and collision
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

using namespace sf;


int main() {

    int keyTime = 8;
    RenderWindow window(VideoMode(640, 500), "Simple Game");
    window.setFramerateLimit(60);

    CircleShape hoop;
    int dir=0;
    hoop.setRadius(50);
    hoop.setFillColor(Color::Black);
    hoop.setOutlineThickness(2);
    hoop.setOutlineColor(Color::Blue);
    hoop.setPosition(Vector2f(0,10.0f));


    CircleShape ball;
    bool isShot = false;
    ball.setRadius(20);
    ball.setFillColor(Color::Red);
    ball.setPosition(Vector2f(0,window.getSize().y-ball.getRadius()*3));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        //Update Hoop
        if(hoop.getPosition().x<=0)
            dir = 1;
        else if(hoop.getPosition().x + 2*hoop.getRadius() >= window.getSize().x)
            dir = 0;

        if(dir == 0)
        {
            hoop.move(-5,0);
        }
        else
        {
            hoop.move(5,0);
        }


        //Update Ball
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            isShot = true;
        }

        if(!isShot)
            ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y); //relative to the window
        else
            ball.move(0,-5.0f);

        //Collision
        if(ball.getPosition().y <0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
        {
            isShot = false;
            ball.setPosition(ball.getPosition().x,window.getSize().y-ball.getRadius()*3);
        }

        window.clear(Color::White);
        window.draw(hoop);
        window.draw(ball);
        window.display();
    }
    return 0;
}

