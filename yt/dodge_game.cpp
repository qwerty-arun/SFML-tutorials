//Dodge the cat with dog
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
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace sf;


int main() {
    srand(time(NULL));

    RenderWindow window(VideoMode(640, 500), "Cat Do(d)ge");
    window.setFramerateLimit(60);

    //Cat
    Texture catTex;
    Sprite cat;

   if(! catTex.loadFromFile("textures/cat.png"))
        throw "Could not load cat.png!";

    cat.setTexture(catTex);
    cat.setScale(Vector2f(0.5f,0.5f));
    int catSpawnTimer = 15;


    std::vector<Sprite> cats;
    cats.push_back(Sprite(cat));

    //Doge
    Texture dogeTex;
    Sprite doge;
    int hp = 10;
    RectangleShape hpBar;
    hpBar.setFillColor(Color::Red);
    hpBar.setSize(Vector2f(hp*20.f, 20.0f));
    hpBar.setPosition(200.f,10.f);

    if(!dogeTex.loadFromFile("textures/doge.png"))
        throw "Could not load doge.png";

    doge.setTexture(dogeTex);
    doge.setScale(Vector2f(0.1f,0.1f));

    while (window.isOpen() && hp>0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        //update
        //
        //
        //doge(player)
        doge.setPosition(doge.getPosition().x, Mouse::getPosition(window).y);
        if(doge.getPosition().y > window.getSize().y-doge.getGlobalBounds().height)
            doge.setPosition(doge.getPosition().x,window.getSize().y-doge.getGlobalBounds().height);

        if(doge.getPosition().y <0)
            doge.setPosition(doge.getPosition().x,0);
        //
        //
        //cats(enemies)
        for(size_t i = 0; i < cats.size(); i++)
        {
            cats[i].move(-5.f,0.f);
            if(cats[i].getPosition().x < 0 - cat.getGlobalBounds().width) //dont erase just as cats touch the left boundary, after its right edge moves, only then we have to erase
                cats.erase(cats.begin()+i); //remove cats
        }
        if(catSpawnTimer < 20)
            catSpawnTimer++;

        if(catSpawnTimer >=20)
        {
            cat.setPosition(window.getSize().x, rand()%int(window.getSize().y - cat.getGlobalBounds().height));
            cats.push_back(Sprite(cat));
            catSpawnTimer= 0;
        }

        //Collision
        for(size_t i =0;i<cats.size();i++)
        {
            if(doge.getGlobalBounds().intersects(cats[i].getGlobalBounds()))
            {
                cats.erase(cats.begin()+i);
                hp--;
            }
        }
        //UI update
        hpBar.setSize(Vector2f(hp*20.f,20.f));

        //draw
        window.clear(Color::White);

        window.draw(doge);
        for(size_t i = 0; i<cats.size();i++)
        {
            window.draw(cats[i]);
        }
        //UI
        window.draw(hpBar);
        window.display();
    }
return 0;
}
