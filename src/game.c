#include "valley.h"

void gameLoop(Windows * windows)
{
    Game * game = gameSetup(); // Generate the world and the player

   
    Position position_offset; // Offset suggested by the user's inputs (if move up -> y-1 , x)
    int input = 0;
    int end_condition = 0;

    while (end_condition == 0) // Main loop
    {
        wclear(windows->text_window);

        if(game->move_count < 10)
        {
            mvwprintw(windows->text_window, 1, 1, "I must hurry, I only got 5 minutes left in the Valley, just enought for a last quest !");
            mvwprintw(windows->text_window, 3, 1, "'Finish the quest within 5 minutes, or you'll lose.'");
            mvwprintw(windows->text_window, 4, 1, "'If your health points reach 0, you'll lose'");
            mvwprintw(windows->text_window, 5, 1, "'To win, finish a quest or get 100 score'");

        }
        game->move_count++;

        position_offset = handleInput(game, windows, input); // Return position offset suggested by current user input
        
        checkPosition(position_offset, game, windows); // Deal with what's where the player wants to move

        //moveMonsters(game);

        render(game, windows); // Update the game's display

        end_condition = checkEndConditions(game);

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
    new_game->move_count = 0;

    mapGeneration(new_game);

    // place the npc giving the quest in the house 
    placeNpcInStructure(new_game->map, new_game->house, new_game->npc);


    MobStruct * mob = genMonster(new_game->map, 10,3,'G');
    
    new_game->start_time = time(NULL);
    
    return new_game;
}

int checkEndConditions (Game * game)
{   
    // Get the current time
    time_t current_time = time(NULL);

    // Calculate elapsed time
    int elapsed_time = difftime(current_time, game->start_time);
    
    
    if (elapsed_time > 300) // Check if elapsed_time is more than 5 minutes (300 seconds)
    {
        return 1;
    }
    else if (game->npc->quest_completed == true) // Check if the quest as been fulfilled
    {
        return 2;
    }
    else if (game->player->score >= 100) // Check if the score reach 100
    {
        return 3;
    }
    else if (game->player->health <= 0) // Check if the player is dead
    {
        return 4;
    }


    return 0;
}