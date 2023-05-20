#include "valley.h"

StructureStruct * StructureSetup(int SIZE, char door, bool chest)
{
	StructureStruct * structure = malloc(sizeof(StructureStruct));
	structure->dimensions.height = SIZE;
    structure->dimensions.width = 2*SIZE;
    structure->door.type = door;
    structure->chest = chest;
    return structure;
}

bool TryToPlacePlayerAndStructuresForMaxTrials(Game * game, int max_trials)
{
    int trials = 0;

    do // Generate a random valid position for the player, house and dungeon while until everything is reachable and not too close to each other
    {
    setRandomSpawn(game); // Set a random valid spawn point for the player
    generateRandomStructurePosition(game->map, game->house);
    generateRandomStructurePosition(game->map, game->dungeon);

    trials++;

        if (trials >= max_trials) // If trials reaches maxTrials, return to create another map
        {
            return FALSE; //map is unvalid
        }

    // Checking if the structures are reachable by the player, not too near from each other and not too near from the player
    } while (!ArePlayerHouseAndDungeonWellPlaced(game)); 

    // Generates house and dungeon in the map array
    generateStructure(game->map, game->house);
    generateStructure(game->map, game->dungeon);
	return TRUE; // map is valid
}

bool ArePlayerHouseAndDungeonWellPlaced(Game * game)
{
    if (isStructureReachableAndNotTooNear(game->map, game->player, game->house, HOUSE_MINIMAL_DISTANCE_FROM_PLAYER) && 
        isStructureReachableAndNotTooNear(game->map, game->player, game->dungeon, DUNGEON_MINIMAL_DISTANCE_FROM_PLAYER) &&
        !isTooNear(game->house->position, game->dungeon->position, HOUSE_MINIMAL_DISTANCE_FROM_DUNGEON))
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool isStructureReachableAndNotTooNear(Map * map, PlayerStruct * player, StructureStruct * structure, int minimal_distance)
{
    // Chekcking if the structure position (top left corner of the structure) is reachable using a BFS pathfinding 
    // and checking if the surroundings of the structure are not stuck with a wall '#'
    // wich could make the structure unreachable by the player
    if (isReachable(map, player->position, structure->position) && !isStructureStuck(map, structure) && !isTooNear(player->position, structure->position, minimal_distance))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool isStructureStuck(Map * map, StructureStruct * structure)
{
    Position pos = structure->position;
    Dimensions dim = structure->dimensions;

    for(int y = pos.y - 1; y < pos.y + dim.height + 1; y++) // Check the surroundings for walls
    {
        for(int x = pos.x - 1; x < pos.x + dim.width + 1; x++)
        {
            if(map->tiles[y][x] == '#')
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}


void generateStructure(Map * map, StructureStruct * structure)
{
    Position pos = structure->position;
    Dimensions dim = structure->dimensions;

    for(int y = pos.y; y < pos.y + dim.height; y++) // Generate a rectangular house with the randomised dimensions y and x
    {
        for(int x = pos.x; x < pos.x + dim.width; x++)
        {
            if(y == pos.y || y == pos.y + dim.height - 1 || x == pos.x || x == pos.x + dim.width - 1) // If extremities, place wall
            {
                map->tiles[y][x] = '#';
                map->colors[y][x] = BLACK_ON_WHITE; // Special color for the walls
            }
            else // If not, place ground
            {
                map->tiles[y][x] = ' ';
                map->colors[y][x] = DEFAULT_ON_DEFAULT;
            }
        }
    }

    PlaceDoorAtRandomSide(map, structure);

}

void generateRandomStructurePosition (Map * map, StructureStruct * structure)
{
    do // Generate valid position inside of the map,, taking in account the size of the house and of the map
    {
        structure->position.y = (rand() % (map->dimensions.height - (structure->dimensions.height + 4))) + 2;
        structure->position.x = (rand() % (map->dimensions.width - (structure->dimensions.width + 4))) + 2;
    } while (map->tiles[structure->position.y][structure->position.x] == '#' || map->tiles[structure->position.y][structure->position.x] == '.');
}