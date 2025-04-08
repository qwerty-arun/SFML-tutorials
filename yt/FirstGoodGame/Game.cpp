# include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game Logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Game 1",sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setScale(0.5f,0.5f);
    this->enemy.setFillColor(sf::Color::White);
    /*this->enemy.setOutlineColor(sf::Color::Green);*/
    /*this->enemy.setOutlineThickness(1.f);*/
}

void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and sets their colors and positions
        - Sets a random position
        - Sets a random color
        - Adds enemy to the vector
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);

    //Spawn the enemy
    this->enemies.push_back(this->enemy);

    //Remove enemies at end of screen
}

void Game::updateEnemies()
{
    /*
        @return void

        - Updates the enemy spawn timer and spawns enemies
            when the total amount of enemies is smaller than the max
        - Moves the enemies down
        - Removes the enemies at the edge of the screen.
    */
    //Updating the timer for enemy spawning
    if(this->enemies.size() <this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer=0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //Move and update the enemies
    for(int i =0;i<this->enemies.size();i++)
    {

        bool deleted = false;

        this->enemies[i].move(0.f,5.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin()+i);
        }

    }

        //Check if clicked upon
        //First do the easy computing first (check if mouse coordinates when clicked are withing bounds, then the heavy computing last)
        //Or 24/7 check if mouse is within bounds, then after clicking, remove the enemy (this is NOT SMART)
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(this->mouseHeld == false)
            {
                this->mouseHeld = true;
                bool deleted = false;
                for(size_t i = 0;i<this->enemies.size() && deleted == false;i++)
                {
                    if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)) //you can use intersects,but contains()'s sole purpose is to check is a point is inside a bound
                    {
                        //Delete the enemy
                        deleted = true;
                        this->enemies.erase(this->enemies.begin()+i);
                        //Gain points
                        this->points += 1.f;
                    }
                }
            }
        }
        else
        {
            this->mouseHeld = false;
        }
}

void Game::renderEnemies()
{
    //Rendering all the enemies
    for(auto& e: this->enemies)
    {
        this->window->draw(e);
    }
}

void::Game::updateMousePositions()
{
    /* 
        @ return void
        Updates mouse position relative to window ()
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}



//Constructors
Game::Game()
{
    this->initVariables();
    this->initWindow(); //maintain the order because in intiVar(), window is nullptr
    this->initEnemies();
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
    this->updateMousePositions();
    this->updateEnemies();
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
    this->renderEnemies();
    this->window->display();
}
