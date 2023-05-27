#include "valley.h"

PlayerStruct * playerSetup()
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->score = 0;
	player->skin = '@'; // Set player char
	player->inventory_size = 4;

	initPlayerInventory(player);
	player->inventory[1] = genPotion(10, 5, "Heal potion");

	player->max_health = PLAYER_MAX_HEALTH;
	player->health = player->max_health;
	player->base_attack = PLAYER_BASE_ATTACK;
	player->attack = player->base_attack;

	return player;
}

void initPlayerInventory(PlayerStruct * player)
{
	int size = player->inventory_size;
	player->inventory = malloc(sizeof(Item*) * size);


    for(int i = 0; i < size; i++)
    {
        player->inventory[i] = malloc(sizeof(Item));
		player->inventory[i] = NULL;
    }
}

void setRandomSpawn(Game * game)
{
	Position random;
	do {
		random.y = rand() % (game->map->dimensions.height - 2) + 1;
		random.x = rand() % (game->map->dimensions.width - 2) + 1;
	} while (game->map->tiles[random.y][random.x] == '#' || game->map->tiles[random.y][random.x] == '.');

	game->player->position.y = random.y;
	game->player->position.x = random.x;
}


Position handleInput(Game * game, Windows * windows, int input) 
{
	Position position_offset;

	position_offset.y = 0;
	position_offset.x = 0;

	switch(input) 
	{
		case 'z' :
		case 'Z' :
			position_offset.y = - 1;
			position_offset.x = 0;
			mobPursuit(game->player->position, game->mob, game->map, game->index_mob, game->move_count);
			break;
		case 's' :
		case 'S' :
			position_offset.y = + 1;
			position_offset.x = 0;
			mobPursuit(game->player->position, game->mob, game->map, game->index_mob, game->move_count);
			break;
		case 'q' :
		case 'Q' :
			position_offset.y = 0;
			position_offset.x = - 1;
			mobPursuit(game->player->position, game->mob, game->map, game->index_mob, game->move_count);
			break;
		case 'd' :
		case 'D' :
			position_offset.y = 0;
			position_offset.x = + 1;
			mobPursuit(game->player->position, game->mob, game->map, game->index_mob, game->move_count);
			break;
		case 'e':
		case 'E':
			wclear(windows->text_window);
			handleInteraction(game, windows);
			break;
		case 'a':
		case 'A':
			wclear(windows->text_window);
			potionInteraction(game->player, windows);
			break;
		default :
			break;	
	}
	return position_offset;
}

void handleInteraction(Game * game, Windows * windows)
{
	Position object_position;
	
	for (int y = game->player->position.y - 1; y <= game->player->position.y + 1; y++)
	{
		for (int x = game->player->position.x - 1; x <= game->player->position.x + 1; x++)
		{
			switch (game->map->tiles[y][x])
			{
				case '*':
					flowerInteraction(game,windows, y,x);
					break;
				case 'W':
					ManageWizardInteractions(game, windows);
					break;
				case 'N':
					ManageNecroInteractions(game,windows);
					break;
				case '%':
					if (game->player->attack >= 3) // 3 is the minimal required attack to break
					{
						game->map->tiles[y][x] = ' ';
						mvwprintw(windows->text_window, 1, 1, "Take that");
					}
					else
					{
						mvwprintw(windows->text_window, 1, 1, "Dammit ! The door is obstructed and im too weak to break it.");
					}
					break;
				case 'O':
					game->map->tiles[y][x] = ' ';
					game->player->score += 1;
					break;
				case '$':
					object_position.y = y;
					object_position.x = x;
					manageChestInteraction(game, windows, object_position);
					break;
				case '=':
					mvwprintw(windows->text_window, 1, 1, "Broken, just like me.");
				case 'G':
				case 'X':
				case 'T':
					game->index_mob=trackMob(game->numb_monster, game->mob, game->player);
					combat(game,game->map, game->player, game->mob, game->index_mob);
					break;	
				default:
					break;
			}
		}
	}
}

void checkPosition(Position position_offset, Game * game, Windows * windows)
{
	Position new;
	new.y = game->player->position.y + position_offset.y;
    new.x = game->player->position.x + position_offset.x;

	if (new.y >= 0 && new.y < game->map->dimensions.height && new.x >= 0 && new.x < game->map->dimensions.width)
    {
		playerMove(position_offset, game, windows); // Manage how to move the player
	}
}


void playerMove(Position position_offset, Game * game, Windows * windows)
{
	Position new_position;

	new_position.y = game->player->position.y + position_offset.y;
	new_position.x = game->player->position.x + position_offset.x;



	switch (game->map->tiles[new_position.y][new_position.x])
	{
		// If crossable
		case ' ':
		case ',':
		case '"':
		case '*':
		case '|':
		game->player->position = new_position;
			break;

		// If movable
		case 'O':
			handleMovable(&game->player->position, game->map, position_offset);
			break;

		default: // If not crossable
			break;
	}
}

bool handleMovable(Position * pushing_position, Map * map, Position position_offset)
{
	
    Position new_pushing_position; // position of the pushing object (firstly being the player)
    Position new_pushed_position; // position of the pushed object (firstly being a movable)

    new_pushing_position.y = pushing_position->y + position_offset.y; // new positions suggested by the player displacement input
    new_pushing_position.x = pushing_position->x + position_offset.x;

    new_pushed_position.y = new_pushing_position.y + position_offset.y;
    new_pushed_position.x = new_pushing_position.x + position_offset.x;

    switch(map->tiles[new_pushed_position.y][new_pushed_position.x]) // Check the tile where we want to move the movable
    {
		case 'O':
            if (handleMovable(&new_pushing_position, map, position_offset) == 0) // recursively calls the function to check the tile behind the string of movable
			{
				return 0; // 0 is returned by every call if the last call returns 0
			}
        case ',':
        case '"':
        case '*':
        case ' ':
            // If we can move the string of 'O' move the last and then the followings returning 1 to each call 

            map->tiles[new_pushed_position.y][new_pushed_position.x] = 'O';
			map->colors[new_pushed_position.y][new_pushed_position.x] = WHITE_ON_DEFAULT;

			// Move the 0 then restore the original tile state
			map->tiles[new_pushing_position.y][new_pushing_position.x] = map->tiles_save[new_pushing_position.y][new_pushing_position.x];
			map->colors[new_pushing_position.y][new_pushing_position.x] = map->colors_save[new_pushing_position.y][new_pushing_position.x];
			return 1;
			
        default:
			return 0; // If the there is finally an unmovable being the string, return 0, which will return 0
    }
}
