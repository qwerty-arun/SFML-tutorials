# include "Game.h"
//constructor
Game::Game()
{
    initVariables();
    initWindow();
}

//destructor
Game::~Game()
{
    delete this->window;
}

const bool Game::running() const
{
    return this->window->isOpen();
}

//Public Functions
//update
void Game::update()
{
        this->pollEvents();
        if(enemySpawnTimer <20)
            enemySpawnTimer++;
        if(enemySpawnTimer>=20)
        {
            this->enemy.setPosition((rand() % int(this->window->getSize().x - enemy.getRadius())),0.f);
            this->enemies.push_back(enemy);
            enemySpawnTimer = 0;
        }
    //enemies move downward
    for(size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].move(0.f,5.f);
            if(enemies[i].getPosition().y> window->getSize().y)
            {
                    enemies.erase(enemies.begin()+i);
            }
        }
}

//poll events
void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type == sf::Event::Closed || (sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape))
        {
            this->window->close();
        }
    }
}

//rendering
void Game::render()
{
    this->window->clear();
    for(int i =0;i<this->enemies.size();i++)
    {
        this->window->draw(this->enemies[i]);
    }
    this->window->display();
}

//Private Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->enemy.setRadius(30);
    this->enemy.setFillColor(sf::Color::White);
    this->enemy.setOrigin(30,30);
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800,600),"First Game Using Classes", sf::Style::Default);
}

