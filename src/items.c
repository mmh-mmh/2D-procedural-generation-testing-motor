#include "valley.h"

Item * genSword(int damage, int durability, char *name_sword)
{
	Item * blade = malloc(sizeof(Item));
	blade->mainItems.weapon = malloc(sizeof(Weaponstats));

	if(blade==NULL || blade->mainItems.weapon ==NULL)
	{
		exit(0);
	}
	strcpy(blade->name,name_sword);
	blade->mainItems.weapon->damage = damage;
	blade->mainItems.weapon->durability = durability;
	return blade;
}

Item * genPotion(int heal_points, int quantity, char * name_potion)
{
	Item * medicine = malloc(sizeof(Item));
	medicine->mainItems.potions = malloc(sizeof(Potion));

	if(medicine==NULL||medicine->mainItems.potions == NULL)
		exit(0);
		
	strcpy(medicine->name,name_potion);
	medicine->mainItems.potions->heal = heal_points;
	medicine->mainItems.potions->quantity = quantity;
		
	return medicine;
}

Item * genObject(int quantity, char skin, char * name_object)
{
	Item * article = malloc(sizeof(Item));
	strcpy(article->name, name_object);
	article->mainItems.object = malloc(sizeof(Object));
	article->mainItems.object->quantity = quantity;
	article->mainItems.object->skin = skin;
	return article;
}

void potionInteraction(PlayerStruct * player, Windows * windows) // if the player still has potions he can use it to recover a number of points until player->max_health points of life
{
	
	
	if((*player->inventory[1]).mainItems.potions->quantity>0)
	{
		(*player->inventory[1]).mainItems.potions->quantity--;
		player->health+=(*player->inventory[1]).mainItems.potions->heal;
		if(player->health>player->max_health)
		{
			player->health=player->max_health;
		}
		mvwprintw(windows->text_window, 1, 1, "Gulp, gulp... I still have %d bottles of potions in my bag", (*player->inventory[1]).mainItems.potions->quantity);

	} 
	else 
	{
		mvwprintw(windows->text_window, 1, 1, "I ran out of potions, dammit! ");
	}
}

void flowerInteraction(Game * game, Windows * windows, int y, int x)
{
	if(game->player->inventory[3]->mainItems.object->quantity < 10)
	{
		game->map->tiles[y][x] = ' ';
		game->map->colors[y][x] = WHITE_ON_DEFAULT;
		game->player->inventory[3]->mainItems.object->quantity++;
		mvwprintw(windows->text_window, 1, 1, "mmmmhhhhh.....flowies. I got %d pieces of them in my bag",game->player->inventory[3]->mainItems.object->quantity);
		game->player->score += 1;
		
	}else 
	{
		mvwprintw(windows->text_window, 1, 1, "My bag is full with flowers, it's becoming compulsive, I should stop... ");

	}
}
