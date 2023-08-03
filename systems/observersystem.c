#include <components.h>
#include <geometry.h>

void ObserverSystem(Body *bodies, Observer *observers, Player *players)
{
    Point playerPos = PointFromVector(bodies[PLAYER_ID].pos);
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Observer *observer = &observers[i];
        if (!observer->valid)
            continue;
        observer->canSeePlayer = true;
        observer->playerPos = playerPos;
    }
}