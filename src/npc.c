#include "valley.h"

npcStruct * wizardSetup()
{
    npcStruct * npc = malloc(sizeof(npcStruct));
    npc->skin = 'W';

    npc->name = malloc(sizeof(char*));
    strcpy(npc->name, "Strange Wizard");

    return npc;
}

void placeWizardInHouse(Game * game)
{

do
{
game->npc->position.y = game->house->position.y + HOUSE_SIZE/2;
game->npc->position.x = game->house->position.x + HOUSE_SIZE;
} while (isNear(game->npc->position, game->house->position));

game->map->tiles[game->npc->position.y][game->npc->position.x] = game->npc->skin;
game->map->colors[game->npc->position.y][game->npc->position.x] = 4;
}


void ManageWizardInteractions(Game * game, Windows * windows)
{
    mvwprintw(windows->text_window, 1, 1, "%s : HEY YOU. Go get me my magic hat you weird looking boy.", game->npc->name);
    mvwprintw(windows->text_window, 2, 1, "%s : I forgot it in this monsterful dungeon near my house.", game->npc->name);
    mvwprintw(windows->text_window, 3, 1, "%s : Take this sword, you're gonna need it to break the entrance.", game->npc->name);
   
    mvwprintw(windows->text_window, 5, 1, "'What an old looking and grumpy looking man' you think. ");

}