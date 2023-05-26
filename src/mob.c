#include "valley.h"

/*
 * The function bellow, generates an array of the type MobStruct which creates random monsters of 3 different types 
 * and its status with valable positions.
 */

MobStruct * genMonster(Map * map,int nb_monster)
{
int health, attack;
	char skin;

	MobStruct * monster = malloc(sizeof(MobStruct)*nb_monster);
	int mob;
	for (int i = 0; i < nb_monster; i++)
	{
		mob=rand()%4;
		switch (mob)
		{
		case 1: 
			health=24;
			attack=4;
			skin='X'; //X for spider 
			break;
		case 2: 
			health=10;
			attack=2;
			skin='G'; //G for goblin
			break;
		case 3:
			health=30;
			attack=5;
			skin='T'; //T for Troll
			break;
		}

		monster[i].health = health;
		monster[i].attack = attack;
		monster[i].skin = skin;
		monster[i].alive = true;
		monster[i].triggered = false;
		do
		{
			monster[i].coordinate.y = rand() % (map->dimensions.height - 2) + 1;
			monster[i].coordinate.x = rand() % (map->dimensions.width - 2) + 1;
		} while (map->tiles[monster[i].coordinate.y][monster[i].coordinate.x] == '.' || map->tiles[monster[i].coordinate.y ][monster[i].coordinate.x] == '#');

		map->tiles[monster[i].coordinate.y][monster[i].coordinate.x] = monster[i].skin;
		map->colors[monster[i].coordinate.y][monster[i].coordinate.x] = WHITE_ON_DEFAULT;
	}
	return monster;
}

int trackMob(int numb_monster, MobStruct *mob, PlayerStruct *player)
{

    /*
        This function tracks the current monster the player is fighting and returns its index in the array of monsters.
        The player must be engaged in melee combat, and the chosen monster must be alive and have the smallest distance to the player.
    */
    int closestMonsterIndex = -1;
    double minDistance = 2; // Set minimum distance 

    for (int i = 0; i < numb_monster; i++) // get the monster having the closest distance below the minDistance 
    {
        double dx = pow(player->position.x - mob[i].coordinate.x, 2);
        double dy = pow(player->position.y - mob[i].coordinate.y, 2);
        double distance = sqrt(dx + dy);

        if (distance <= minDistance && mob[i].alive)
        {
            minDistance = distance;
            closestMonsterIndex = i;
        }
    }
        return closestMonsterIndex;
}

/*
 * The function below manages the movement of the mobs: once a mob is attacked by the player, the function calculates the distance between the monster and the player
 * and according the mob's x and y coordinate, the mob will move towards the player
 *the function also assures the mob isnt entering in cases which are crossable such as: # . and @ 
 *  
 * */

 void mobPursuit(Position playerpos, MobStruct * mob, Map * map, int index_mob, int game_move_count)
{

	 if(isTooNear(playerpos, mob[index_mob].coordinate, 6) && mob[index_mob].alive == true && mob[index_mob].triggered == true)
	{
		if(game_move_count%2 == 0)
		{
			return;
		}

		/* step left */
		if((abs((mob[index_mob].coordinate.x - 1) - playerpos.x) < abs(mob[index_mob].coordinate.x - playerpos.x))&&
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1] != '.')&&
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1] != '@')&&
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1] != '#'))

		{	
			mob[index_mob].coordinate.x--;
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = mob[index_mob].skin;
			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = WHITE_ON_DEFAULT;

			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1] = map->colors_save[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1];
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1] = map->tiles_save[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1];
		}		
		/* step right */
		else if ((abs((mob[index_mob].coordinate.x + 1) - playerpos.x) < abs(mob[index_mob].coordinate.x - playerpos.x))&&
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1] != '.')&& //parts of the map the mob can't cross
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1] != '@')&&
		 (map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x + 1] != '#'))
		{
			mob[index_mob].coordinate.x++;
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = mob[index_mob].skin;
			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = WHITE_ON_DEFAULT;

			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1] = map->colors_save[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1];
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x-1] = map->tiles_save[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x - 1];
		}
		/* step down*/
		else if ((abs((mob[index_mob].coordinate.y + 1) - playerpos.y) < abs(mob[index_mob].coordinate.y - playerpos.y))&&
		(map->tiles[mob[index_mob].coordinate.y + 1][mob[index_mob].coordinate.x] != '.')&&
		(map->tiles[mob[index_mob].coordinate.y + 1][mob[index_mob].coordinate.x] != '@')&&
		(map->tiles[mob[index_mob].coordinate.y + 1][mob[index_mob].coordinate.x] != '#'))
		{
			mob[index_mob].coordinate.y++;
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = mob[index_mob].skin;
			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = WHITE_ON_DEFAULT;

			map->colors[mob[index_mob].coordinate.y-1][mob[index_mob].coordinate.x] = map->colors_save[mob[index_mob].coordinate.y-1][mob[index_mob].coordinate.x];
			map->tiles[mob[index_mob].coordinate.y-1][mob[index_mob].coordinate.x] = map->tiles_save[mob[index_mob].coordinate.y-1][mob[index_mob].coordinate.x];
		}
		/* step up */
		else if ((abs((mob[index_mob].coordinate.y - 1) - playerpos.y) < abs(mob[index_mob].coordinate.y - playerpos.y)) &&
		 (map->tiles[mob[index_mob].coordinate.y - 1][mob[index_mob].coordinate.x] != '.')&&
		 (map->tiles[mob[index_mob].coordinate.y - 1][mob[index_mob].coordinate.x] != '@')&&
		  (map->tiles[mob[index_mob].coordinate.y - 1][mob[index_mob].coordinate.x] != '#'))
		{
			mob[index_mob].coordinate.y--;
			map->tiles[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = mob[index_mob].skin;
			map->colors[mob[index_mob].coordinate.y][mob[index_mob].coordinate.x] = WHITE_ON_DEFAULT;

			map->colors[mob[index_mob].coordinate.y+1][mob[index_mob].coordinate.x] = map->colors_save[mob[index_mob].coordinate.y+1][mob[index_mob].coordinate.x];
			map->tiles[mob[index_mob].coordinate.y+1][mob[index_mob].coordinate.x] = map->tiles_save[mob[index_mob].coordinate.y+1][mob[index_mob].coordinate.x];
		}
		mob->triggered=false;

	}
}
