// the eraser featue doesn't work correctly
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
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
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Smooth Paint App",sf::Style::Resize|sf::Style::Close);
    sf::VertexArray lines(sf::LineStrip); // Stores the line segments
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

    sf::RectangleShape clear_box;clear_box.setSize(sf::Vector2f(40.0f,40.0f));clear_box.setFillColor(sf::Color(128.0f,128.f,128.0f)); clear_box.setPosition(sf::Vector2f(0.f,0.f));
    sf::RectangleShape eraser_box;eraser_box.setSize(sf::Vector2f(40.0f,40.0f));eraser_box.setFillColor(sf::Color(51.0f,51.f,22.0f)); eraser_box.setPosition(sf::Vector2f(40.f,0.f));
    bool clear_on = false;
    bool eraser_on = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) // use if(event.mouseButton.button == sf::Mouse::Left) if you want only lines
                    {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        /*sf::Vector2f mousePos(event.mouseButton.x,event.mouseButton.y);*/
                        if(red.getGlobalBounds().contains((sf::Vector2f)mousePos)) //note that type casting is happening from into to float so its not a problem as there is not info loss
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
                        if(clear_box.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                           clear_on = true;
                        }
                        if(eraser_box.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                           eraser_on = true;
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
        if(isDrawing && !eraser_on)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            currentStroke.append(sf::Vertex(sf::Vector2f(mousePos),currentColor));
        }
                    if(clear_on)
                    {
                        /*strokes.erase(sf::Mouse::getPosition(window));*/
                        strokes.clear();
                        clear_on=false;
                    }
                    
                    /*if(eraser_on)*/
                    /*{*/
                    /*    sf::Vector2i mousePos = sf::Mouse::getPosition(window);*/
                    /*    sf::VertexArray toBeErasedStroke(sf::LineStrip);// stores the current stroke*/
                    /*    toBeErasedStroke.append(sf::Vertex(sf::Vector2f(mousePos),currentColor));*/
                    /*    strokes.erase(sf::Vertex(sf::Vector2f(mousePos),sf::Color::White),sf::Vertex(sf::Vector2f(mousePos)+1.f,sf::Color::White));*/
                    /*    eraser_on = false;*/
                    /*}*/
/*if (eraser_on) {*/
/*            if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)*/
/*            {*/
/*    sf::Vector2i mousePos = sf::Mouse::getPosition(window);*/
/*    sf::Vector2f eraserPosition(mousePos.x, mousePos.y);*/
/*    float eraserRadius = 10.0f; // Eraser size*/
/**/
/*    // Iterate through all stored strokes*/
/*    for (auto& stroke : strokes) {*/
/*        for (size_t i = 0; i < stroke.getVertexCount(); ++i) {*/
/*            sf::Vector2f point = stroke[i].position;*/
/**/
/*            // Check if the point is inside the eraser radius*/
/*            if (std::hypot(point.x - eraserPosition.x, point.y - eraserPosition.y) < eraserRadius) {*/
/*                // Remove the point by shifting remaining points*/
/*                stroke[i].color = sf::Color::White; // Change color to background instead of removing*/
/*            }*/
/*        }*/
/*    }*/
/*        if(event.type == event.MouseButtonReleased)*/
/*        {*/
/*            eraser_on = false;*/
/*        }*/
/*    }*/
/*}*/
        /*else{*/
        /*    eraser_on = false;*/
        /*}*/
        if (eraser_on && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f eraserPosition(mousePos.x, mousePos.y);
    float eraserRadius = 10.0f; // Eraser size

    // Iterate through all stored strokes
    for (auto& stroke : strokes) {
        for (size_t i = 0; i < stroke.getVertexCount(); ++i) {
            sf::Vector2f point = stroke[i].position;
            
            // Check if the point is inside the eraser radius
            if (std::hypot(point.x - eraserPosition.x, point.y - eraserPosition.y) < eraserRadius) {
                stroke[i].color = sf::Color::White; // "Erase" by turning white
            }
        }
    }
} else {
    eraser_on = false; // Disable eraser mode once mouse is released
}

        window.clear(sf::Color::White);
        //draw all previous strokes
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
        window.draw(clear_box);
        window.draw(eraser_box);
        window.display();
    }
    return 0;
}
