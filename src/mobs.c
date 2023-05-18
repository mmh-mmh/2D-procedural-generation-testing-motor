	#include "valley.h"



Position findEmptyZoneStart(char *map[MAP_WIDTH], int height, int width) {
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

    return start;  // Return (-1, -1) if no empty zone is found
}


bool IsPositionValid(Position pos, int gap, char skin, int height, int width, char *map[MAP_WIDTH])
{
	
	if(pos.x>=gap && pos.x<=width-gap&&pos.y>=gap && pos.y<=height-gap) //forces the square area to be in the bonds of the map
	{
			for(int coordy=pos.y-gap; coordy<pos.y+gap; coordy++)
			{
				for(int coordx=pos.x-gap;coordx<pos.x+gap; coordx++)
				{
					if(map[coordy][coordx]=='.'||map[coordy][coordx]=='#')
					{	
						return true;
					}	
					if(map[coordy][coordx]==skin)
					{	
						return true;
						
					}	
				}
			}
	}
	return false;
}

Position genPos(char *map[MAP_WIDTH], char skin,int height,int width)
{

	if(map==NULL||height<0||height>MAP_HEIGHT||width<0||width>MAP_WIDTH)
		exit(0);
		
	int count =0,coordx=0,coordy=0, gap=20;
	Position pos, start;
	
	srand(time(NULL));
	do
	{
		start=findEmptyZoneStart(map, MAP_HEIGHT, MAP_WIDTH);
	}while(start.x<0 && start.y<0);
	do 
	{
		pos.x= start.x+rand()%(width-start.x);
		pos.y=start.y+rand()%(height-start.y); 
	}
	while(!IsPositionValid(pos,gap,skin, height, width, map));
	return pos;
}


MobStruct * genMonster( char * map[MAP_WIDTH], int health, int attack, char skin)
{
	if(health < 0||health > 30)
        exit(0);
	if(attack<0||attack>30)
        exit(0);
	if(skin != 'G'&& skin != 'X')
		exit(0);
	MobStruct * monster=malloc(sizeof(MobStruct));
	
		monster->health=health;
		monster->attack=attack;
		monster->skin=skin;
		monster->coordinate= genPos(map, skin, MAP_HEIGHT-1,MAP_WIDTH-1);
		map[monster->coordinate.y][monster->coordinate.x]=monster->skin;
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
		return genMonster(map,5,2,'G');
	}
	return NULL;
}
void AddMob(char ** map)
{
    MobStruct *mob=MobSetUp(rand()%2,map);
    if(mob== NULL)
		exit(0);
	mvprintw(0,0,"x: %d  y: %d", mob->coordinate.x,mob->coordinate.y);


}
