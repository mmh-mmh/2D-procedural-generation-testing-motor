#include "valley.h"

Game * gameSetup()
{
    Game * new_game = malloc(sizeof(Game));
    new_game->player = playerSetup(); // malloc and set player stats
    new_game->map = createMap(MAP_HEIGHT, MAP_WIDTH); // malloc and create an empty map
    new_game->house = houseSetup(); // malloc house, set size and position
    new_game->npc = wizardSetup(); // malloc and set position

    // Generate proceduraly ground and walls of the map, then try for max_trials to put the house and the player in the map
    // If max_trials reached, regenerate a map
    int max_trials = 10000;
    do
    {
        mapProceduralGeneration(new_game->map); // Proceduraly generate map inside the walls;
    } while ( TryToPlaceHouseAndPlayerForMaxTrials(new_game, max_trials) == FALSE );

    placeWizardInHouse(new_game);

	genMonster(new_game->map, 20,5,'T');
	genMonster(new_game->map, 12,6,'X');
	genMonster(new_game->map, 10,3,'G');
    
    
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
        
        wclear(windows->text_window);
        checkPosition(position_offset, game, windows); // Deal with what's where the player wants to move
        //moveMonsters(game);

        render(game, windows); // Update the game's display

        input = getch(); // Get user input
    }
}
