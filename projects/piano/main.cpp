#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <cmath>
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800,600), "Piano Stuff");
    window.setFramerateLimit(60);

    sf::Texture background;
    if(!background.loadFromFile("octave.png"))
        return -1;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);

backgroundSprite.setScale(
    float(window.getSize().x) / background.getSize().x,
    float(window.getSize().y) / background.getSize().y
);

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("wav_c1.wav"))
        return -1;
    Sound C1(buffer);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if(Mouse::isButtonPressed(Mouse::Left) && ((Mouse::getPosition().x >=30 && Mouse::getPosition().x <=85 && Mouse::getPosition().y>=120 && Mouse::getPosition().y<=590) || (Mouse::getPosition().x>85 && Mouse::getPosition().x<=140 && Mouse::getPosition().y<=590 && Mouse::getPosition().y>=420)))
        {
                C1.play();
        }
        if(Mouse::isButtonPressed(Mouse::Left) && (Mouse::getPosition().x>=85 && Mouse::getPosition().x<=160 && Mouse::getPosition().y>=120 && Mouse::getPosition().y<=420))
        {
            sf::SoundBuffer buffer1;
            if(!buffer1.loadFromFile("wav_c1.wav"))
                return -1;
            Sound C1Sharp(buffer1);
            C1Sharp.setPitch(1.059f);
            C1Sharp.play();
        }
        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    return 0;
}

