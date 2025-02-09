#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Vertex Array - square");

    // Create a VertexArray with 3 points (square)
    /*sf::VertexArray square(sf::PrimitiveType::LineStrip, 4);*/
    sf::VertexArray square(sf::PrimitiveType::Quads,4);
    square[0].position = sf::Vector2f(100, 100);
    square[1].position = sf::Vector2f(100, 150);
    square[2].position = sf::Vector2f(150, 150);
    square[3].position = sf::Vector2f(150, 100);
    sf::Vector2f position(250,250);
    sf::Vector2f velocity(-0.5f,0.6f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for(int i{};i<=3;i++)
            square[i].color= sf::Color(rand()%256, rand()%256,rand()%256);
        position+=velocity;

        for(int i{};i<=3;i++)
        {
            square[i].position.x +=velocity.x;
            square[i].position.y +=velocity.y;
        }
        if(square[0].position.x <=0 || square[0].position.x >=500)
        {
                velocity.x = -velocity.x;
        }
        if(square[0].position.y <=0 || square[0].position.y >=500)
        {
                velocity.y = -velocity.y;
        }
        if(square[2].position.y >=500)
        {
                velocity.y = -velocity.y;
        }
        if(square[2].position.x >=500)
        {
                velocity.x = -velocity.x;
        }
        window.clear();
        window.draw(square);
        window.display();
    }
    return 0;
}
