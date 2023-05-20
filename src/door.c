#include "valley.h"

void PlaceDoorAtRandomSide(Map * map, StructureStruct * structure)
{
    Position pos = structure->position;
    Dimensions dim = structure->dimensions;
   
	switch (rand()%2) // Generate a random door position, up, down, left or right
	{
		case 0:
			structure->door.position.x = pos.x;
			structure->door.position.y = pos.y + dim.height/2;
			break;
		case 1:
			structure->door.position.x = pos.x + dim.width-1;
			structure->door.position.y = pos.y + dim.height/2;
			break;
	}
    
    map->tiles[structure->door.position.y][structure->door.position.x] = structure->door.type; // Place the door
    map->colors[structure->door.position.y][structure->door.position.x] = 2; 
}