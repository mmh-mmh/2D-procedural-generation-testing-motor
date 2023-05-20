#include "valley.h"

void gameLoop(Windows * windows)
{
    Game * game = gameSetup(); // Generate the world and the player

   
    Position position_offset; // Offset suggested by the user's inputs (if move up -> y-1 , x)
    int input = 0;

    while (input != 'a') // Main loop
    {
        wclear(windows->text_window);

        position_offset = handleInput(game, windows, input); // Return position offset suggested by current user input
        
        checkPosition(position_offset, game, windows); // Deal with what's where the player wants to move

        //moveMonsters(game);

        render(game, windows); // Update the game's display

        input = getch(); // Get user input
    }
}

Game * gameSetup()
{
    Game * new_game = malloc(sizeof(Game));
    new_game->player = playerSetup(); // malloc and set player stats
    new_game->map = mapSetup(MAP_HEIGHT, MAP_WIDTH); // malloc map
    new_game->house = StructureSetup(HOUSE_SIZE, '|', false); // malloc structure, set size, door, and if chest
    new_game->dungeon = StructureSetup(DUNGEON_SIZE, '%', true);
    new_game->npc = wizardSetup(); // malloc and set position


    // Generate proceduraly ground and walls of the map, then try for max_trials to place the player and the structures in the map
    // They must verify certain conditions (not being too near, being reachable...)
    // If max_trials reached, regenerate a map and retry
    int max_trials = 10000;
    do
    {   
        clearMap(new_game->map); // Sets map to default : empty with # on extremities
        mapProceduralGeneration(new_game->map); // Proceduraly generate map inside the walls;
    } while ( !TryToPlacePlayerAndStructuresForMaxTrials(new_game, max_trials));

    new_game->map->tiles_save = copyMap(new_game->map); // copy the tiles to help handling movables later (replacing tile after they moved)

    
    // place the npc giving the quest in the house 
    placeNpcInStructure(new_game->map, new_game->house, new_game->npc);


    MobStruct * mob = genMonster(new_game->map, 10,3,'G');
    
    
    return new_game;
}