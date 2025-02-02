#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512), "SFML tutorial",sf::Style::Close| sf::Style::Resize); //setting up our window
    while(window.isOpen()) //infinite while loop
    {
        sf::Event evnt; //event like close, resize, text etc.
        while(window.pollEvent(evnt))
        {
            switch (evnt.type) {
                case sf::Event::Closed: //can't use evnt.Closed , inside the switch statment, you can't use the parameters inside from the created class, so we need to call the Closed() from the Class itself
                    window.close();
                break;

                case sf::Event::Resized: //if we resize he window
                    /*std::cout << "New Window Width: "<<evnt.size.width<<" New Window Height: " << evnt.size.height<<std::endl;*/
                    printf("New Window widht: %i New Window height: %i\n",evnt.size.width,evnt.size.height); //everytime we resize the window, it displays the new size on the terminal
                break;

                case sf::Event::TextEntered:
                    if(evnt.text.unicode<128)
                    printf("%c",evnt.text.unicode);
                break;
            }
            if(evnt.type == evnt.Closed)
            {
                window.close();
            }
        }
    }
    return 0;
}
