#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace sf;
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(1920,1080), "View Stuff",Style::Default);


    View mainView;
    mainView.setSize(1920,1080);


    RectangleShape player;
    player.setSize(Vector2f(50.f,50.f));
    player.setPosition(500.f,500.f);
    
    RectangleShape object;
    object.setSize(Vector2f(50.f,50.f));
    object.setPosition(600.f,600.f);

    RectangleShape UIElement;
    UIElement.setSize(Vector2f(300.f,50.f));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }
        // Update
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            player.move(-5.f,0.f);
        }

        else if(Keyboard::isKeyPressed(Keyboard::D))
        {
            player.move(5.f,0.f);
        }
        
        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            player.move(0.f,-5.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            player.move(0.f,5.f);
        }
        mainView.setCenter(player.getPosition());
        //Draw
        //
        window.clear();

        //Draw Stuff
        window.setView(mainView);
        window.draw(player);
        window.draw(object);
    
        //Draw UI
        window.setView(window.getDefaultView());
        window.draw(UIElement);

        //Finished drawing
        window.display();
    }
    return 0;
}
