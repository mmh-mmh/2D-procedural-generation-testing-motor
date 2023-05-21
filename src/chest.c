#include <valley.h>

void genChestInMiddleOfStructure(Map * map, StructureStruct * structure)
{   
    Position pos = structure->chest_position;
    structure->chest_interaction_count = 0;
    pos.y = structure->position.y + structure->dimensions.height / 2;
    pos.x = structure->position.x + structure->dimensions.width / 2;
    map->tiles[pos.y][pos.x] = '$';
    map->colors[pos.y][pos.x] = YELLOW_ON_DEFAULT;

    // Surrounding the chest with 'O'
    for (int y = pos.y - 2; y <= pos.y + 2; y++)
    {
        for (int x = pos.x - 4; x <= pos.x + 4; x++)
        {
            if (y != pos.y || x != pos.x)
            {
                map->tiles[y][x] = 'O';
            }
        }
    }
}

void manageChestInteraction(Game * game, Windows * windows, Position chest_position)
{   
    if (game->dungeon->chest_interaction_count == 0)
    {
        mvwprintw(windows->text_window, 1, 1, "Looks like this chest is sealed with an old spell...");
        mvwprintw(windows->text_window, 4, 30, "...Yeah im definitely breaking it");
    }
    else if (game->dungeon->chest_interaction_count == 1)
    {
        mvwprintw(windows->text_window, 1, 1, "Ouch..One more..");
    }
    else if (game->dungeon->chest_interaction_count == 2)
    {   
        game->map->tiles[chest_position.y][chest_position.x] = '=';
        mvwprintw(windows->text_window, 1, 1, "Done.");
        mvwprintw(windows->text_window, 3, 1, "'You Found the wizard's hat'");

        game->player->inventory[2] = genObject(1, '^', "Smelly hat");
    }

    game->dungeon->chest_interaction_count++;
}