	#include "valley.h"

MobStruct * genMonster( int health, int attack, char skin,int height,int width)
{
	if(health < 0||health > 30)
        exit(0);
	if(attack<0||attack>30)
        exit(0);
	if(skin != 'V'&& skin != 'X')
		exit(0);
	MobStruct * monster=malloc(sizeof(MobStruct));
	monster->health=health;
	monster->attack=attack;
	monster->skin=skin;
	
    monster->coordinate.x=2+rand()%height;
    monster->coordinate.y=2+rand()%width;
	return monster;
}

MobStruct * MobSetUp(int mobtype)
{
	
	if(mobtype<0 &&mobtype>2)
        exit(0);
	if(mobtype==0)
	{
		return genMonster(10,4,'X',MAP_HEIGHT,MAP_WIDTH);
	} else if (mobtype==1)
	{
		return genMonster(5,2,'V',MAP_HEIGHT,MAP_WIDTH);
	}
	return NULL;
}
