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