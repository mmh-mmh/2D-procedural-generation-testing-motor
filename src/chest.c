#include <valley.h>

void genChestInMiddleOfStructure(Map * map, StructureStruct * structure)
{   
    Position chest;
    chest.y = structure->position.y + structure->dimensions.height / 2;
    chest.x = structure->position.x + structure->dimensions.width / 2;
    map->tiles[chest.y][chest.x] = '$';
    map->colors[chest.y][chest.x] = YELLOW_ON_DEFAULT;

    // Surrounding the chest with 'O'
    for (int y = chest.y - 1; y <= chest.y + 1; y++)
    {
        for (int x = chest.x - 1; x <= chest.x + 1; x++)
        {
            if (y != chest.y || x != chest.x)
            {
                map->tiles[y][x] = 'O';
            }
        }
    }
}