//2D shooter game
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace sf;

class Bullet
{
    public:
        CircleShape shape;
        Vector2f currVelocity;
        float maxSpeed;

        Bullet(float radius = 5.f) : currVelocity(0.f,0.f),maxSpeed(15.f) 
        {
            this->shape.setFillColor(Color::Red);
            this->shape.setRadius(radius);
        }
};
// Length of Vector: |V| = sqrt(V.x^2+V.y^2)
// Normalize Vector: U = V / |V|

int main() {
    srand(time(NULL));

    RenderWindow window(VideoMode(800, 600), "360 Shooter");
    window.setFramerateLimit(60);

    //Player
    CircleShape player(25);
    player.setFillColor(Color::White);

    //Bullefts
    Bullet b1;

    std::vector<Bullet> bullets;

    //Enemy
    RectangleShape enemy;
    enemy.setFillColor(Color::Magenta);
    enemy.setSize(Vector2f(50.f,50.f));
    int spawnCounter = 20;
    std::vector<RectangleShape> enemies;
    

    //Vectors
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        //Update Vectors
        playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        aimDirNorm.x = aimDir.x / (std::sqrt(pow(aimDir.x,2)+ pow(aimDir.y,2)));
        aimDirNorm.y = aimDir.y / (std::sqrt(pow(aimDir.x,2)+ pow(aimDir.y,2)));


        //Player
        if(Keyboard::isKeyPressed(Keyboard::A))
            player.move(-10.f,0.f);

        if(Keyboard::isKeyPressed(Keyboard::D))
            player.move(10.f,0.f);

        if(Keyboard::isKeyPressed(Keyboard::W))
            player.move(0.f,-10.f);

        if(Keyboard::isKeyPressed(Keyboard::S))
            player.move(0.f,10.f);


        //Enemy
        if(spawnCounter<50)
            spawnCounter++;
        if(spawnCounter>=50 && enemies.size()<50)
        {
            enemy.setPosition(rand()%window.getSize().x,rand()%window.getSize().y);
            enemies.push_back(RectangleShape(enemy));
            spawnCounter = 0;
        }

        //Shooting
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            b1.shape.setPosition(playerCenter);
            b1.currVelocity = aimDirNorm * b1.maxSpeed;
            bullets.push_back(Bullet(b1));
        }
        for(size_t i = 0;i< bullets.size(); i++)
        {
            //Out of bounds
            bullets[i].shape.move(bullets[i].currVelocity);
            if(bullets[i].shape.getPosition().x<0 || bullets[i].shape.getPosition().x > window.getSize().x ||bullets[i].shape.getPosition().y<0 || bullets[i].shape.getPosition().y >window.getSize().y)
            {
                bullets.erase(bullets.begin()+i);
            }
            else
            {
                //Enemy Collision
                for(size_t k = 0;k<enemies.size();k++)
                  {
                     if(bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
                    {
                        bullets.erase(bullets.begin()+i);
                        enemies.erase(enemies.begin()+k);
                        break;
                    }
                 }

            }

        }

        //Draw
        window.clear();

        for(size_t i = 0;i<enemies.size();i++)
        {
            window.draw(enemies[i]);
        }

        window.draw(player);

        for(size_t i = 0;i< bullets.size(); i++)
        {
            window.draw(bullets[i].shape);
        }
        window.display();
    }
return 0;
}
