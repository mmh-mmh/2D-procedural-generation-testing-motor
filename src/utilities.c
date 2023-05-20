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