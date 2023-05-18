#include "valley.h"

Position findEmptyZoneStart(char *map[MAP_WIDTH], int height, int width) 
{
    Position start;
    start.x = -1;
    start.y = -1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] != '.' && map[y][x] != '#') {
                start.x = x;
                start.y = y;
                return start;
            }
        }
    }

}

MobStruct * genMonster( char * map[MAP_WIDTH], int health, int attack, char skin)
{
	if(health < 0||health > 30)
        exit(0);
	if(attack<0||attack>30)
        exit(0);
	if(skin != 'G'&& skin != 'X' && skin != 'T' )
		exit(0);
	MobStruct * monster=malloc(sizeof(MobStruct));
	Position start;
	start=findEmptyZoneStart(map, MAP_HEIGHT, MAP_WIDTH);
	monster->health=health;
	monster->attack=attack;
	monster->skin=skin;

	monster->coordinate.x= start.x+rand()%(MAP_WIDTH-start.x);
	monster->coordinate.y= -start.y+rand()%(MAP_HEIGHT-start.y);
	map[monster->coordinate.y][monster->coordinate.x]=monster->skin;
	return monster;
}
