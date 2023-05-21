#include "valley.h"

bool isNear(Position a, Position b)
{
    for (int diffy = - 1; diffy <= 1; diffy ++)
    {
        for (int diffx = - 1; diffx <= 1; diffx ++)
        {
            if (a.y + diffy == b.y && a.x + diffx == b.x)
            {
                return true;
            }
        }
    }
    return false;
}

bool isTooNear (Position a, Position b, int distance_limit)
{   
    // The square root of the sum of the squared distances
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double abDistance = sqrt(dx * dx + dy * dy);

    if (abDistance < distance_limit)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

char ** copyCharArrayOfArray(char ** array, Dimensions dimensions)
{
	char ** char_array_copy = malloc(dimensions.height * sizeof(char *));

	for (int y = 0; y < dimensions.height; y++)
	{
		char_array_copy[y] = malloc(dimensions.width * sizeof(char));

		for (int x = 0; x < dimensions.width; x++)
		{
				char_array_copy[y][x] = array[y][x];
		}
	}
	return char_array_copy;
}

int ** copyIntArrayOfArray(int ** array, Dimensions dimensions)
{
	int ** int_array_copy = malloc(dimensions.height * sizeof(int *));

	for (int y = 0; y < dimensions.height; y++)
	{
		int_array_copy[y] = malloc(dimensions.width * sizeof(int));

		for (int x = 0; x < dimensions.width; x++)
		{
				int_array_copy[y][x] = array[y][x];
		}
	}
	return int_array_copy;	
}