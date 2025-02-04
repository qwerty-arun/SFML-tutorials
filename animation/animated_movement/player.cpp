#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include"player.h"
Player::Player(sf::Texture* texture, sf::Vector2u ImageCount, float swithTime,float speed) : animation(texture, ImageCount,swithTime)
{
    this->speed = speed;
    row=0;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f,150.0f));
    body.setPosition(206.f,206.f);
    body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f,0.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -=speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x +=speed * deltaTime;
    if(movement.x == 0.0f)
    {
        row=0;
    }
    else
    {
        row = 1;
        if(movement.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    animation.Update(row, deltaTime,faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
