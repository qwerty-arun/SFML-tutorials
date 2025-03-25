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

void Update(int &keyTime, RectangleShape& square);
void Draw(RenderWindow& window, RectangleShape& square); //you don't have to draw to window

int main() {

    int keyTime = 8;
    RenderWindow window(VideoMode(500, 500), "Example: WASD");
    window.setFramerateLimit(60);

    RectangleShape square(Vector2f(100,100));
    square.setFillColor(Color::Red);
    square.setPosition(window.getSize().x/2.0, window.getSize().y/2.0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        Update(keyTime,square);
        Draw(window,square);
        window.display();
    }

    return 0;
}

void Update(int &keyTime, RectangleShape& square)
{
    if(keyTime<8)
        keyTime++;
    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        square.move(-5.f,0.f);
        keyTime=0;
    }
    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        square.move(5.f,0.f);
        keyTime=0;
    }
    if(Keyboard::isKeyPressed(Keyboard::W))
    {
        square.move(0.f,-5.f);
        keyTime=0;
    }
    if(Keyboard::isKeyPressed(Keyboard::S))
    {
        square.move(0.f,5.f);
        keyTime=0;
    }
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        square.setFillColor(Color::Blue);
        /*keyTime=0;*/
    }
    else
        square.setFillColor(Color::Red);
}

void Draw(RenderWindow& window,RectangleShape& square)
{
    window.clear(Color::White);
    window.draw(square);
    //Draw stuff
    window.display();
}

