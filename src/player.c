#include "valley.h"

PlayerStruct * playerSetup()
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->position.y = MAP_HEIGHT/2;
	player->position.x = MAP_WIDTH/2;
	player->skin = '@';
	
	return player;
}

void SetRandomSpawn(Game * game)
{
	int height = game->map->dimensions.height;
	int width = game->map->dimensions.width;
	char **tiles = game->map->tiles;

	int y, x;
	do {
		y = rand() % (height - 2) + 1;
		x = rand() % (width - 2) + 1;
	} while (tiles[y][x] == '#' || tiles[y][x] == '.');

	game->player->position.y = y;
	game->player->position.x = x;
}


Position handleInput(int input)
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
		default :
			break;
			
	}
	return position_offset;
}


void checkPosition(Position position_offset, Game * game)
{
	Position new;
	new.y = game->player->position.y + position_offset.y;
    new.x = game->player->position.x + position_offset.x;

	if (new.y >= 0 && new.y < game->map->dimensions.height && new.x >= 0 && new.x < game->map->dimensions.width)
    	{
    	switch (game->map->tiles[game->player->position.y + position_offset.y][game->player->position.x + position_offset.x])
    	{
    	    default:
				playerMove(position_offset, game);
    	        break;
     		case 'X':
    	    case 'G':
     	       //combat(...);
				break;
		}
	}
}


void playerMove(Position position_offset, Game * game)
{
	Position new_position;

	new_position.y = game->player->position.y + position_offset.y;
	new_position.x = game->player->position.x + position_offset.x;



	switch (game->map->tiles[new_position.y][new_position.x])
	{
		case '#':
		case '.':
		case '&':
			break;
		case 'O':
			//handleMovable();
		break;
		default:
			game->player->position = new_position;
			break;
	}
}
