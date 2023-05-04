


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

typedef struct
{
	Item **backpack;

}Player;


Item ** genSword(int damage, int durability, char *name_sword)
{
	Item ** blade=malloc(sizeof(Item*));
	*blade=malloc(sizeof(Item));
	(*blade)->type=0;
	strcpy((*blade)->name,name_sword);
	(*blade)->mainItems.weapon=malloc(sizeof(Weaponstats));
	(*blade)->mainItems.weapon->damage=damage;
	(*blade)->mainItems.weapon->durability=durability;

	return blade;
}



int main(int argc, char **argv)
{
	Player p1;
	p1.backpack=malloc(sizeof(Player*));
	p1.backpack=genSword(1,20,"starter");
	printf("%s\n",(*p1.backpack)->name);
	printf("%d\n",(*p1.backpack)->mainItems.weapon->damage);
	printf("%d\n",(*p1.backpack)->mainItems.weapon->durability);
 	return 0;
}

