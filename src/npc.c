#include "valley.h"

npcStruct * wizardSetup()
{
    npcStruct * npc = malloc(sizeof(npcStruct));
    npc->skin = 'W';

    npc->name = malloc(sizeof(char*));
    strcpy(npc->name, "Strange Wizard");

    npc->interactions_count = 0;

    return npc;
}

void placeNpcInStructure(Map * map, StructureStruct * structure, npcStruct * npc)
{

    do
    {
        npc->position.y = structure->position.y + structure->dimensions.height/2;
        npc->position.x = structure->position.x + structure->dimensions.width/2;
    } while (isNear(npc->position, structure->position));

   map->tiles[npc->position.y][npc->position.x] = npc->skin;
    map->colors[npc->position.y][npc->position.x] = BLUE_ON_DEFAULT;
}


void ManageWizardInteractions (Game * game, Windows * windows)
{
    mvwprintw(windows->text_window, 1, 1, "%s : HEY YOU. Go get me my magic hat you weird looking boy.", game->npc->name);
    mvwprintw(windows->text_window, 2, 1, "%s : I forgot it in this monsterful dungeon in [%d,%d].", game->npc->name, game->dungeon->position.y,game->dungeon->position.x);
    mvwprintw(windows->text_window, 3, 1, "%s : Take this sword, you're gonna need it to break the entrance.", game->npc->name);
    mvwprintw(windows->text_window, 5, 1, "'What an old and grumpy looking man' you think. ");

    if (game->npc->interactions_count == 0)
    {
        game->player->inventory[0] = genSword(5, 200, "rusty sword");
    }

    game->npc->interactions_count++;
}