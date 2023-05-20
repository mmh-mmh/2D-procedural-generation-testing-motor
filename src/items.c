#include "valley.h"

Item * genSword(int damage, int durability, char *name_sword)
{
	Item * blade = malloc(sizeof(Item));
	
	if(blade==NULL)
		exit(0);
		strcpy(blade->name,name_sword);
		blade->mainItems.weapon = malloc(sizeof(Weaponstats));

	if(blade->mainItems.weapon ==NULL)
		exit(0);

	blade->mainItems.weapon->damage = damage;
	blade->mainItems.weapon->durability = durability;

	return blade;
}

Item * genPotion(int heal_points, int quantity, char * name_potion)
{
	Item * medicine = malloc(sizeof(Item));
	medicine->mainItems.potions = malloc(sizeof(Potion));

	if(medicine==NULL)
		exit(0);

	if(medicine->mainItems.potions == NULL)
		exit(0);
	
	strcpy(medicine->name,name_potion);

	medicine->mainItems.potions->heal = heal_points;
	medicine->mainItems.potions->quantity = quantity;
		
	return medicine;
}

Item * genObject(int quantity, char skin, char * name_object, Position coordinate)
{
	Item * article = malloc(sizeof(Item));
	strcpy(article->name, name_object);
	article->mainItems.object = malloc(sizeof(Object));
	article->mainItems.object->quantity = quantity;
	article->mainItems.object->skin = skin;
	article->mainItems.object->coordinate->x = coordinate.x; // if you wanna 
	article->mainItems.object->coordinate->y = coordinate.y;
	return article;
}
