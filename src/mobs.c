	#include "valley.h"

Position genPos(char *map[MAP_WIDTH], char skin,int height,int width)
{
	srand(time(NULL));
	if(map==NULL||height<0||height>MAP_HEIGHT||width<0||width>MAP_WIDTH)
		exit(0);
	int count =0,coordx=0,coordy=0, gap=20;
	Position pos;
	do 
	{
		pos.x= 2+rand()%width;
		pos.y=2+rand()%height; 
		if(pos.x>=gap && pos.x<=width-gap&&pos.y>=gap && pos.y<=height-gap) //forces the square area to be in the bonds of the map
		{
			for(coordy=pos.y-gap; coordy<pos.y+gap; coordy++)
			{
				for(coordx=pos.x-gap;coordx<pos.x+gap; coordx++)
				{
					if(map[coordy][coordx]=='.'||map[coordy][coordx]=='#'|| map[coordy][coordx]==skin)
					{
						count=0;
						break;
					}
					else
					{
						count++;
					}
				}
				if(map[coordy][coordx]=='.'||map[coordy][coordx]=='#')
					break;
			}
		}
	}
	while(count!=coordx*coordy);
	return pos;
}
MobStruct * genMonster( char * map[MAP_WIDTH], int health, int attack, char skin)
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
	
    monster->coordinate= genPos(map, skin, MAP_HEIGHT-2,MAP_WIDTH-2);
	return monster;
}

MobStruct * MobSetUp(int mobtype, char *map[MAP_WIDTH])
{
	
	if(mobtype<0 &&mobtype>2)
        exit(0);
	if(mobtype==0)
	{
		return genMonster(map,10,4,'X');
	} else if (mobtype==1)
	{
		return genMonster(map,5,2,'V');
	}
	return NULL;
}
void AddMob(char ** map)
{
    MobStruct *mob=malloc(sizeof(MobStruct));
    if(mob== NULL)
		exit(0);
    mob=MobSetUp(0,map);
    if(mob== NULL)
		exit(0);
	map[mob->coordinate.y][mob->coordinate.x]=mob->skin;

}
