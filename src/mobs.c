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
    monster->coordinate.x=1;
    monster->coordinate.y=1;
	return monster;
}

MobStruct * Mobselect(int mobtype)
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
