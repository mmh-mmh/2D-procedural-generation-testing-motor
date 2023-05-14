	#include "valley.h"

MobStruct * genMonster( int health, int attack, char skin)
{
    if(health < 0 || health > 30);
        exit(0);
    if (attack<0 ||  health>30)
        exit(0);
    if(skin != 'V'|| skin != 'X')
        exit(0);
	MobStruct * monster;
	monster=malloc(sizeof(MobStruct*));
	monster->health=health;
	monster->attack=attack;
	monster->skin=skin;
    monster->coordinate.x=50;
    monster->coordinate.y=50;
	return monster;
}

MobStruct * MobSetUp(int mobtype)
{
	if(mobtype<0 &&mobtype>2);
        exit(0);
	if(mobtype==0)
	{
		return genMonster(10,4,'X');
	} else if (mobtype==1)
	{
		return genMonster(5,2,'V');
	}
	return NULL;
}

void AddMob(Map *map)
{
    if(map==NULL)
        exit(0);

    MobStruct *mob=MobSetUp(0);
    if(mob!= NULL)
		map->tiles[mob->coordinate.y][mob->coordinate.x]=mob->skin;

}
