#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Perspective Projection");

    vector<Vector3f> vertices;

    vertices.push_back(Vector3f(100.f,100.f,1.f));
    vertices.push_back(Vector3f(200.f,100.f,1.f));
    vertices.push_back(Vector3f(200.f,200.f,1.f));
    vertices.push_back(Vector3f(100.f,200.f,1.f));
    vertices.push_back(Vector3f(100.f,100.f,1.f));

    vertices.push_back(Vector3f(100.f,100.f,1.2f));
    vertices.push_back(Vector3f(200.f,100.f,1.2f));
    vertices.push_back(Vector3f(200.f,200.f,1.2f));
    vertices.push_back(Vector3f(100.f,200.f,1.2f));
    vertices.push_back(Vector3f(100.f,100.f,1.2f));



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //perspective projection
    vector<Vertex> vertices2Dfront; 
    for(int i=0;i<vertices.size()/2;i++)
    {
        vertices2Dfront.push_back(sf::Vertex(Vector2f(vertices[i].x/vertices[i].z, vertices[i].y/vertices[i].z),Color::White)); 
    }

    vector<Vertex> vertices2Dback; 
    for(int i=vertices.size()/2;i<vertices.size();i++)
    {
        vertices2Dback.push_back(sf::Vertex(Vector2f(vertices[i].x/vertices[i].z, vertices[i].y/vertices[i].z),Color::White)); 
    }

    vector<vector<Vertex>> edges(4);
    for(int i=0;i<4;i++)
    {
        edges[i].push_back(sf::Vertex(Vector2f(vertices2Dfront[i].position.x,vertices2Dfront[i].position.y),Color::White)); 
        edges[i].push_back(sf::Vertex(Vector2f(vertices2Dback[i].position.x,vertices2Dback[i].position.y),Color::White)); 
    }

        window.clear();
        if(!vertices2Dfront.empty())
            window.draw(vertices2Dfront.data(),vertices2Dfront.size(),sf::LinesStrip);

        if(!vertices2Dback.empty())
            window.draw(vertices2Dback.data(),vertices2Dback.size(),sf::LinesStrip);

        for(int i=0;i<4;i++)
        {
                window.draw(edges[i].data(),edges[i].size(),sf::LinesStrip);
        }

        window.display();
    }

    return 0;
}
