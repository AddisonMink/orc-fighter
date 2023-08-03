#include <components.h>
#include <geometry.h>

void ObserverSystem(Body *bodies, Observer *observers, Player *players)
{
    bool playerExists = players[PLAYER_ID].valid;
    Point playerPos = PointFromVector(bodies[PLAYER_ID].pos);
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Observer *observer = &observers[i];
        if (!observer->valid)
            continue;

        if (playerExists)
        {
            observer->canSeePlayer = true;
            observer->playerPos = playerPos;
        }
        else
            observer->canSeePlayer = false;
    }
}