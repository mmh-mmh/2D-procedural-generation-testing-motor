#include "valley.h"

PlayerStruct * playerSetup()
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->skin = '@'; // Set player char
	player->inventory_size = 3;
	initPlayerInventory(player);
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
			break;
		case 's' :
		case 'S' :
			position_offset.y = + 1;
			position_offset.x = 0;
			break;
		case 'q' :
		case 'Q' :
			position_offset.y = 0;
			position_offset.x = - 1;
			break;
		case 'd' :
		case 'D' :
			position_offset.y = 0;
			position_offset.x = + 1;
			break;

		case 'e':
			handleInteraction(game, windows);
		default :
			break;	
	}
	return position_offset;
}

void handleInteraction(Game * game, Windows * windows)
{
	for (int y = game->player->position.y - 1; y <= game->player->position.y + 1; y++)
	{
		for (int x = game->player->position.x - 1; x <= game->player->position.x + 1; x++)
		{
			switch (game->map->tiles[y][x])
			{
				case 'W':
					ManageWizardInteractions(game, windows);
					break;


				case '%':
					if (game->player->attack >= 3) // 3 is the minimal required attack to break
					{
						game->map->tiles[y][x] = ' ';
					}
					else
					{
						mvwprintw(windows->text_window, 1, 1, "Dammit ! The door is obstructed and im too weak to break it.");
					}
					break;


				case 'G':
					//combat()
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
		// If not crossable
		case '#': 
		case '.':
		case 'W':
		case '%':
		case '$':
			break;

		// If movable
		case 'O': 
			handleMovable(&game->player->position, game->map, position_offset);
		break;

		default: // If crossable
			game->player->position = new_position;
			break;
	}
}

void handleMovable(Position * movingPosition, Map * map, Position position_offset)
{
    Position newMovingPosition;
    Position newMovedPosition;

    newMovingPosition.y = movingPosition->y + position_offset.y;
    newMovingPosition.x = movingPosition->x + position_offset.x;

    newMovedPosition.y = newMovingPosition.y + position_offset.y;
    newMovedPosition.x = newMovingPosition.x + position_offset.x;

    switch(map->tiles[newMovedPosition.y][newMovedPosition.x])
    {
        case ',':
        case '"':
        case '*':
        case ' ':
            // If the new moved position is empty, move the 'O' there
            map->tiles[newMovedPosition.y][newMovedPosition.x] = 'O';

            // Update the player's position
            movingPosition->y = newMovingPosition.y;
            movingPosition->x = newMovingPosition.x;
            break;

        case 'O':
            // If the new moved position has an 'O', move it recursively first
            handleMovable(&newMovedPosition, map, position_offset);

            // Only after moving the next 'O' do we clear the current 'O'
            map->tiles[newMovingPosition.y][newMovingPosition.x] = map->tiles_save[newMovingPosition.y][newMovingPosition.x];

            // Also update the player's position after moving the next 'O'
            movingPosition->y = newMovingPosition.y;
            movingPosition->x = newMovingPosition.x;
            break;

        default:
            break;
    }
}
