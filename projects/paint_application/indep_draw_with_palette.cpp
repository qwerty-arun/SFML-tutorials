#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Smooth Paint App",sf::Style::Resize|sf::Style::Close);

    sf::Color currentColor = sf::Color::Black;  // Default color

    std::vector<sf::VertexArray> strokes; //stores multiple independent strokes
    sf::VertexArray currentStroke(sf::LineStrip);// stores the current stroke
    bool isDrawing = false; //flag to check if the mouse is pressed
    
    // Below is the color palette displayed on the right of the window
    sf::RectangleShape red; red.setSize(sf::Vector2f(40.0f,40.0f)); red.setFillColor(sf::Color::Red); red.setPosition(sf::Vector2f(460.0f,0.0f));
    sf::RectangleShape blue;blue.setSize(sf::Vector2f(40.0f,40.0f));blue.setFillColor(sf::Color::Blue);blue.setPosition(sf::Vector2f(460.0f,40.0f));
    sf::RectangleShape yellow;yellow.setSize(sf::Vector2f(40.0f,40.0f));yellow.setFillColor(sf::Color::Yellow);yellow.setPosition(sf::Vector2f(460.0f,80.0f));
    sf::RectangleShape green;green.setSize(sf::Vector2f(40.0f,40.0f));green.setFillColor(sf::Color::Green);green.setPosition(sf::Vector2f(460.0f,120.0f));
    sf::RectangleShape black;black.setSize(sf::Vector2f(40.0f,40.0f));black.setFillColor(sf::Color::Black);black.setPosition(sf::Vector2f(460.0f,160.0f));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) // use if(event.mouseButton.button == sf::Mouse::Left) if you want only lines
                    {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        /*sf::Vector2f mousePos(event.mouseButton.x,event.mouseButton.y);*/
                        if(red.getGlobalBounds().contains((sf::Vector2f)mousePos)) //not that type casting is happening from into to float so its not a problem as there is not info loss
                        {
                            currentColor=sf::Color::Red;
                        }
                        if(blue.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Blue;
                        }
                        if(yellow.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Yellow;
                        }
                        if(green.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Green;
                        }
                        if(black.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Black;
                        }
                    }

                    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        currentStroke = sf::VertexArray(sf::LineStrip); //reset stroke
                        isDrawing=true;
                    }
                    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(currentStroke.getVertexCount()>1)
                        {
                            strokes.push_back(currentStroke);
                        }
                         isDrawing= false;
                    }
            }

        if(isDrawing)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            currentStroke.append(sf::Vertex(sf::Vector2f(mousePos),currentColor));
        }
        window.clear(sf::Color::White);
        for(auto& stroke : strokes)
        {
            window.draw((stroke));
        }
        //draw the current stroke while the user is still drawing
        if(isDrawing)
        {
            window.draw(currentStroke);
        }
        window.draw(red);
        window.draw(blue);
        window.draw(yellow);
        window.draw(green);
        window.draw(black);
        window.display();
    }
    return 0;
}
