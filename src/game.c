#include "valley.h"

Game * gameSetup()
{
    Game * new_game = malloc(sizeof(Game));
    new_game->player = playerSetup(); // malloc and set player stats
    new_game->map = createMap(MAP_HEIGHT, MAP_WIDTH); // malloc and create an empty map
    new_game->house = houseSetup(); // malloc house, set size and position

    int max_trials = 1000;
    do
    {
        printw("MapTried");
        mapProceduralGeneration(new_game->map); // Proceduraly generate map inside the walls;

    } while ( TryToPlaceHouseAndPlayerForMaxTrials(new_game, max_trials) == FALSE );


	genMonster(new_game->map->tiles, 20,5,'T');
	genMonster(new_game->map->tiles, 12,6,'X');
	genMonster(new_game->map->tiles, 10,3,'G');
    
    
    return new_game;
}


void gameLoop(Windows * windows)
{
    Game * game = gameSetup(); // Generate the world and the player

   
    Position position_offset; // Offset suggested by the user's inputs (if move up -> y-1 , x)
    int input = 0;

    while (input != 'a') // Main loop
    {
        position_offset = handleInput(input); // Return position offset suggested by current user input
        
        checkPosition(position_offset, game); // Deal with what's where the player wants to move
        //moveMonsters(game);

        render(game, windows); // Update the game display

        input = getch(); // Get user input
    }
}
