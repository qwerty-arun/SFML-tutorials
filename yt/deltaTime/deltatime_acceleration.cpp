#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace sf;
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(800, 600), "Acceleration");
    /*window.setFramerateLimit(20);*/


    //dt at 60fps = 0.016s

    RectangleShape shape;
    shape.setFillColor(Color::White);
    shape.setSize(Vector2f(50,50));
    Clock clock;
    float dt;
    float multiplier = 60.f;

    Vector2f currentVelocity;
    Vector2f direction;
    float maxVelocity = 25.f;
    float acceleration = 1.f;
    float drag = 0.5;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }
        dt = clock.restart().asSeconds();

        //Update
        //Acceleration
        direction = Vector2f(0.f,0.f); //every frame it resets
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            direction.x = -1.f;
            if(currentVelocity.x > -maxVelocity)
                currentVelocity.x += acceleration * direction.x * dt * multiplier;
        }

        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            direction.x = 1.f;
            if(currentVelocity.x < maxVelocity)
                currentVelocity.x += acceleration*direction.x * dt * multiplier;
        }

        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            direction.y = -1.f;
            if(currentVelocity.y > -maxVelocity)
                currentVelocity.y += acceleration*direction.y * dt * multiplier;
        }

        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            direction.y = 1.f;
            if(currentVelocity.y < maxVelocity)
                currentVelocity.y += acceleration*direction.y * dt * multiplier;
        }

        //Drag
        if(currentVelocity.x > 0.f)
        {
            currentVelocity.x -= drag * dt * multiplier;
            if(currentVelocity.x < 0.f)
                currentVelocity.x = 0.f;
        }
        else  if (currentVelocity.x < 0.f)
        {
            currentVelocity.x += drag * dt * multiplier;
            if(currentVelocity.x > 0.f)
                currentVelocity.x = 0.f;
        }

        if(currentVelocity.y > 0.f)
        {
            currentVelocity.y -= drag * dt * multiplier;
            if(currentVelocity.y < 0.f)
                currentVelocity.y = 0.f;
        }
        else  if (currentVelocity.y < 0.f)
        {
            currentVelocity.y += drag * dt * multiplier;
            if(currentVelocity.y > 0.f)
                currentVelocity.y = 0.f;
        }

        //Final move
        shape.move(currentVelocity.x * dt * multiplier,currentVelocity.y * dt * multiplier);

        window.clear();

        window.draw(shape);
        window.display();
        std::cout<<dt<<"\n";
    }
    return 0;
}
