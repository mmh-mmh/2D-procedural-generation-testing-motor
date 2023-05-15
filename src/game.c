#include "valley.h"

Game * gameSetup()
{
    Game * new_game = malloc(sizeof(Game));
    new_game->player = playerSetup();
    new_game->map = createMap(MAP_HEIGHT, MAP_WIDTH);
    
    placePlayerAndStructures(new_game);
    
    return new_game;
}

void gameLoop(Windows * windows)
{
    Game * game = gameSetup();

   
    Position position_offset;
    int input = 0;

    while (input != 'a')
    {
        position_offset = handleInput(input);
        
        checkPosition(position_offset, game);
        //moveMonsters(game);

        render(game, windows);

        input = getch();
    }
}