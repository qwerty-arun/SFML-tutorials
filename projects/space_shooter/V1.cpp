#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 1680), "Asteroid game",sf::Style::Resize|sf::Style::Close);
    sf::RectangleShape ship(Vector2f(55,55));
    sf::Clock clock;

    sf::Texture shipTexture;
    shipTexture.loadFromFile("/home/jarvis/work/SFML-tutorials/projects/space_shooter/spaceship.jpeg");
    ship.setTexture(&shipTexture);
    shipTexture.setSmooth(true);
    ship.setOrigin(27.5,27.5);
    ship.setPosition(100,100);

        Texture bulletTex;
        Sprite bullet;

        if(!bulletTex.loadFromFile("../space_invaders/laserbeam.png"))
        {
            std::cerr << "Error: Could not load laserbeam.png" <<std::endl;
            return -1;
        }
        bullet.setTexture(bulletTex);
        bullet.setScale(0.1f,0.5f);
        bullet.rotate(90);
        std::vector<Sprite> bullets;
        bullets.push_back(Sprite(bullet));

        //Asteroids
        RectangleShape asteroid;
        asteroid.setFillColor(Color::White);
        asteroid.setSize(Vector2f(50.f,50.f));
        std::vector<RectangleShape> asteroids;
        asteroids.push_back(RectangleShape(asteroid));


        Vector2f defaultVelocity(5.f,5.f);
        Vector2f shipTip;
        int shootTimer = 0;
        
        int asteroidTimer = 0;
        
        Vector2f bulletDirection;



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
	sf::Vector2f position = ship.getPosition();
shipTip= Vector2f(ship.getPosition().x , ship.getPosition().y);
        float shipRotation = ship.getRotation();

    if(shootTimer < 5)
        {
            shootTimer++;
        }

        if(Keyboard::isKeyPressed(Keyboard::Space) && shootTimer>=5)
        {
            bullet.setRotation(shipRotation);
            bullet.setPosition(shipTip);
            bullets.push_back(Sprite(bullet));
            shootTimer =0;
        }

        for(size_t i = 0; i < bullets.size(); i++)
        {
           /*bullets[i].move(0.f,-10.f);*/
            /*if(shipRotation >=90 && shipRotation <=180)*/
            /*    shipRotation -=90;*/
            /**/
            /*if(shipRotation >=180 && shipRotation <=270)*/
            /*    shipRotation -=180;*/
            /**/
            /*if(shipRotation >=270 && shipRotation <=360)*/
            /*    shipRotation =-shipRotation;*/
            /*if(bullets[i].getPosition().y < 0)*/
            /*{*/
            /*    bullets.erase(bullets.begin()+i);*/
            /*}*/


            float rotationRadians = shipRotation * (3.14159265f / 180.0f);
            bullets[i].move(10 * std::cos(rotationRadians), 10 * std::sin(rotationRadians));
            if (bullets[i].getPosition().y < 0 || bullets[i].getPosition().y > window.getSize().y ||
                bullets[i].getPosition().x < 0 || bullets[i].getPosition().x > window.getSize().x) {
                    bullets.erase(bullets.begin() + i);
                }
        }

        if(asteroidTimer <50)
            asteroidTimer++;
        if(asteroidTimer>=50)
        {
            asteroid.setPosition((rand() % int(window.getSize().x-asteroid.getSize().x)),0.f);
            asteroids.push_back(RectangleShape(asteroid));
            asteroidTimer = 0;
        }
        for(size_t i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].move(0.f,5.f);
            if(asteroids[i].getPosition().y> window.getSize().y)
            {
                    asteroids.erase(asteroids.begin()+i);
            }
        }

        //Collision
        if(!asteroids.empty() && !bullets.empty())
        {
            /*for(size_t i = 0; i < bullets.size(); i++)*/
            /*{*/
            /*    for(size_t j =0; j<asteroids.size();j++)*/
            /*    {*/
            /*        if(bullets[i].getGlobalBounds().intersects(asteroids[j].getGlobalBounds()))*/
            /*        {*/
            /*            bullets.erase(bullets.begin()+i);*/
            /*            asteroids.erase(asteroids.begin()+j);*/
            /*            break;*/
            /*        }*/
            /*    }*/
            /*}*/
            for (int i = bullets.size() - 1; i >= 0; --i) {
    for (int j = asteroids.size() - 1; j >= 0; --j) {
        if (bullets[i].getGlobalBounds().intersects(asteroids[j].getGlobalBounds())) {
            bullets.erase(bullets.begin() + i);
            asteroids.erase(asteroids.begin() + j);
            break;
        }
    }
}


        }

        if(position.x >=window.getSize().x)
        {
            ship.setPosition(0,position.y);
        }
        if(position.x<=0.0)
        {
            ship.setPosition(window.getSize().x,position.y);
        }
        if(position.y >=window.getSize().y)
        {
            ship.setPosition(position.x,0);
        }
        if(position.y<=0.0)
        {
            ship.setPosition(position.x,window.getSize().y);
        }

        //keyboard input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                    ship.move(-5.5f,0.0f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                    ship.move(5.5f,0.0f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                    ship.move(0.0f,-5.5f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                    ship.move(0.0f,5.5f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
            {
                    ship.rotate(-10.f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
            {
                    ship.rotate(10.f);
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
            }
        window.clear(sf::Color::Black);
for(size_t i = 0; i < asteroids.size(); i++)
        {
            window.draw(asteroids[i]);
        }

        for(size_t i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }

	window.draw(ship);
        window.display();
    }
    return 0;
}
