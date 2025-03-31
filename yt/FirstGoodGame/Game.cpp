# include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Game 1",sf::Style::Titlebar | sf::Style::Close);
}
//Constructors
Game::Game()
{
    this->initVariables();
    this->initWindow(); //maintain the order because in intiVar(), window is nullptr
}

//Destructors
Game::~Game()
{
    delete this->window;
}

//Accessors

const bool Game::running() const
{
    return this->window->isOpen();
}


//functions

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type == sf::Event::Closed || (sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape))
            this->window->close();
    }

}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    /*
      @return void

      - clear old frame
      - render new objects
      - display frame in window

      Renders the game objects
    */
    this->window->clear();

    //Draw game objects

    this->window->display();
}
