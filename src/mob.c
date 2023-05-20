#include "valley.h"

MobStruct * genMonster( Map * map, int health, int attack, char skin)
{
	if(health < 0||health > 30)
    {
        exit(0);
    }
	if(attack < 0||attack > 30)
    {
        exit(0);
    }
	if(skin != 'G' && skin != 'X' && skin != 'T' )
    {
        exit(0);
    }

	MobStruct * monster = malloc(sizeof(MobStruct));

	monster->health = health;
	monster->attack = attack;
	monster->skin = skin;

    do
    {
	    monster->coordinate.y = rand() % (map->dimensions.height - 2) + 1;
        monster->coordinate.x = rand() % (map->dimensions.width - 2) + 1;
    } while (map->tiles[monster->coordinate.y][monster->coordinate.x] == '.' || map->tiles[monster->coordinate.y ][monster->coordinate.x] == '#');

	map->tiles[monster->coordinate.y][monster->coordinate.x] = monster->skin;
	return monster;
}