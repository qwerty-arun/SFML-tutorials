//Shooter game with many projectiles and enemies
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
#include <cstddef>
#include <cstdlib>
#include <vector>
using namespace sf;


int main() {
    srand(time(NULL));

    RenderWindow window(VideoMode(640, 500), "Simple Shooter Game");
    window.setFramerateLimit(60);

    //Balls
    CircleShape projectile;
    projectile.setFillColor(Color::Red);
    projectile.setRadius(5.f);
    
    RectangleShape enemy;
    enemy.setFillColor(Color::Blue);
    enemy.setSize(Vector2f(50,50));

    CircleShape player;
    player.setFillColor(Color::White);
    player.setRadius(50.0f);
    player.setPosition(window.getSize().x/2.0 - player.getRadius(),window.getSize().y - player.getRadius()*2 - 10);
    Vector2f playerCenter;
    int shootTimer = 0;


    std::vector<RectangleShape> enemies;
    std::vector<CircleShape> projectiles;
    
    projectiles.push_back(CircleShape(projectile));
    enemies.push_back(RectangleShape(enemy));
    int enemySpawnTimer = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        //UPDATE player
        playerCenter = Vector2f(player.getPosition().x+player.getRadius(), player.getPosition().y + player.getRadius());
            player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);


        //Projectiles
        if(shootTimer<5)
        {
            shootTimer++;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && shootTimer>=5) //Shoot
        {
            projectile.setPosition(playerCenter);
            projectiles.push_back(CircleShape(projectile));
            shootTimer = 0;
        }

        for(size_t i = 0; i < projectiles.size(); i++)
        {
           projectiles[i].move(0.f,-10.f);
            if(projectiles[i].getPosition().y < 0)
            {
                projectiles.erase(projectiles.begin()+i);
            }
        }

        //Enemies
        if(enemySpawnTimer <20)
            enemySpawnTimer++;
        if(enemySpawnTimer>=20)
        {
            enemy.setPosition((rand() % int(window.getSize().x-enemy.getSize().x)),0.f);
            enemies.push_back(RectangleShape(enemy));
            enemySpawnTimer = 0;
        }
        for(size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].move(0.f,5.f);
            if(enemies[i].getPosition().y> window.getSize().y)
            {
                    enemies.erase(enemies.begin()+i);
            }
        }
        //Collision
        if(!enemies.empty() && !projectiles.empty())
        {
            for(size_t i = 0; i < projectiles.size(); i++)
            {
                for(size_t j =0; j<enemies.size();j++)
                {
                    if(projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                    {
                        projectiles.erase(projectiles.begin()+i);
                        enemies.erase(enemies.begin()+j);
                        break;
                    }
                }
            }
        }

        //Draw
        window.clear();
        window.draw(player);

        for(size_t i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i]);
        }

        for(size_t i = 0; i < projectiles.size(); i++)
        {
            window.draw(projectiles[i]);
        }

        window.display();
    }
return 0;
}
