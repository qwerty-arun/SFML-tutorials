#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Selection Sort", sf::Style::Resize | sf::Style::Close);

    float width {10.0f};
    sf::RectangleShape rectangles[10];
    for(int i{0};i<sizeof(rectangles)/sizeof(sf::RectangleShape);i++)
    {
        float height = 20*(rand()%10+1);
        rectangles[i].setSize(sf::Vector2f(width,height)); //randrom height but the rectangles are placed side by side
        rectangles[i].setPosition(200.0+width*i+i,400-height);

        rectangles[i].setFillColor(sf::Color::White);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

//Selection sorting part
    for(int i{0};i<sizeof(rectangles)/sizeof(sf::RectangleShape);i++)
        {
            int smallestIdx = i;
            for(int j{i+1};j<sizeof(rectangles)/sizeof(sf::RectangleShape);j++)
            {
                if(rectangles[j].getPosition().y < rectangles[smallestIdx].getPosition().y)
                {
                    smallestIdx = j;
                    sf::Vector2f size1 = rectangles[i].getSize();
                    sf::Vector2f size2 = rectangles[smallestIdx].getSize();
                    rectangles[i].setSize(sf::Vector2f(size1.x,size2.y));
                    rectangles[smallestIdx].setSize(sf::Vector2f(size2.x,size1.y));
                }
            }
        }
        bool sorted = true;
        window.clear();
        if(sorted)
        {
            for(int i{0};i<sizeof(rectangles)/sizeof(sf::RectangleShape);i++)
            window.draw(rectangles[i]);
        }
        window.display();
        }
    return 0;
}
