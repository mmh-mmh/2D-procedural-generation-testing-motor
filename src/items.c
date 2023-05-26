#include "valley.h"

// The code bellow sets up the attributes of a sword

Item * genSword(int damage, int durability, char *name_sword)
{
	Item * blade = malloc(sizeof(Item));

	blade->mainItems.weapon = malloc(sizeof(Weaponstats));

	if(blade == NULL || blade->mainItems.weapon == NULL)
	{
		exit(0);
	}

	strcpy(blade->name,name_sword);
	blade->mainItems.weapon->damage = damage;
	blade->mainItems.weapon->durability = durability;

	return blade;
}

// The code bellow sets up the attributes of potions
Item * genPotion(int heal_points, int quantity, char * name_potion)
{
	Item * medicine = malloc(sizeof(Item));
	medicine->mainItems.potions = malloc(sizeof(Potion));

	if(medicine==NULL||medicine->mainItems.potions == NULL)
	{
		exit(0);
	}

	strcpy(medicine->name,name_potion);

	medicine->mainItems.potions->heal = heal_points;
	medicine->mainItems.potions->quantity = quantity;

	return medicine;
}
// The code bellow sets up the attributes of objects

Item * genObject(int quantity, char skin, char * name_object)
{
	Item * article = malloc(sizeof(Item));
	strcpy(article->name, name_object);
	article->mainItems.object = malloc(sizeof(Object));
	article->mainItems.object->quantity = quantity;
	article->mainItems.object->skin = skin;
	return article;
}

/*
 * The code bellow handles the interactions of potion consumation, the quantity of potions and 
 * the number of points that the player can heal
 * */
void potionInteraction(PlayerStruct * player, Windows * windows) // if the player still has potions he can use it to recover a number of points until player->max_health points of life
{
	if(player->inventory[1] != NULL && (*player->inventory[1]).mainItems.potions->quantity > 0)
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
		player->inventory[1] = NULL;
		mvwprintw(windows->text_window, 1, 1, "I ran out of potions, dammit! ");
	}
}


/*
 * The code bellow handles the flower's interaction: It will impose a max of flowers that the player can pick up
 * and the player's line
 * */
void flowerInteraction(Game * game, Windows * windows, int y, int x) 
{

	if(game->player->inventory[3] == NULL)
	{
		game->player->inventory[3] = genObject(0, '*', "Flowers");
	}

	if(game->player->inventory[3]->mainItems.object->quantity < FLOWER_CAPACITY_LIMIT)
	{
		game->map->tiles[y][x] = ' ';
		game->map->colors[y][x] = WHITE_ON_DEFAULT;
		game->player->inventory[3]->mainItems.object->quantity++;
		mvwprintw(windows->text_window, 1, 1, "mmmmhhhhh.....flowies. I got %d of them in my bag",game->player->inventory[3]->mainItems.object->quantity);
		game->player->score += 1;

	}else if (game->npc->interactions_count != 0)
	{
		mvwprintw(windows->text_window, 1, 1, "My bag is full with flowers, it's becoming compulsive.");
		mvwprintw(windows->text_window, 1, 20, "Maybe that weird wizard wnats them.. ");
	}
	else 
	{
		mvwprintw(windows->text_window, 1, 1, "My bag is full with flowers, it's becoming really compulsive.");
	}
}
