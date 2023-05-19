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


void giveQuest(npcStruct * npc, Windows * windows)
{
    mvwprintw(windows->text_window, 1, 1, "%s : Felipe est une merde !", npc->name);
}