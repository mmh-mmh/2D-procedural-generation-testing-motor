#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{SWORD_TYPE}WeaponType;
typedef struct //status of the weapon
{
	WeaponType type;
	int damage;
	int durability;
}Weaponstats; 

typedef enum{WEAPON_TYPE, OBJECTS_TYPE,POTIONS_TYPE}itemType;
typedef struct 
{
	itemType type;
	union
	{
		Weaponstats * weapon;
		//~ Object * object; //deseactivé car on ne crée pas les intems comme ùa pour l'instant
		//~ Potions * potions;
	}mainItems;
	char name[256];
}Item;

Item * genSword(int damage, int durability, char *name_sword);

#endif