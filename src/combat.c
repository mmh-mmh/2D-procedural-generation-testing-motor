#include "valley.h"

void combat(Game *game, Map *map, PlayerStruct *player, MobStruct *mob, int index_mob)
{
    if (map == NULL || player == NULL || mob == NULL)
        exit(0);

    mob[index_mob].health -= player->attack; // Mobs will only attack if they are attacked first
    mob[index_mob].triggered = true;

    if (mob[index_mob].health <= 0) // Check if the monster is defeated
    {
        mob[index_mob].alive = false;

        // Update the map by removing the defeated monster
        map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = ' ';

        player->score += 10;
        game->numb_monster--;

        if (game->numb_monster == 0)
        {
            free(mob);
        }
    }
    else
    {
        player->health -= mob[index_mob].attack;
    }
}