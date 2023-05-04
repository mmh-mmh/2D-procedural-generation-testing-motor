#include "inventory.h"

Item * genSword(int damage, int durability, char *name_sword)
{
	Item * blade = malloc(sizeof(Item));
	blade->type = 0;
	strcpy(blade->name,name_sword);
	blade->mainItems.weapon = malloc(sizeof(Weaponstats));
	blade->mainItems.weapon->damage = damage;
	blade->mainItems.weapon->durability = durability;

	return blade;
}

