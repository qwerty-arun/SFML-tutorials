# include "Game.h"
# include <iostream>

int main()
{
    Game game;

    while(game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
    }
    //End of application
    return 0;
}
