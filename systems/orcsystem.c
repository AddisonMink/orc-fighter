#include <orcsystem.h>

void OrcUpdate(
    Body *body,
    Move *move,
    Observer *observer,
    Orc *orc);

void OrcSystem(
    Body *bodies,
    Move *moves,
    Observer *observers,
    Orc *orcs)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        if (!orcs[i].valid)
            continue;

        Body *body = &bodies[i];
        Move *move = &moves[i];
        Observer *oberver = &observers[i];
        Orc *orc = &orcs[i];
        OrcUpdate(body, move, oberver, orc);
    }
}

void OrcUpdate(
    Body *body,
    Move *move,
    Observer *observer,
    Orc *orc)
{
    switch (orc->state)
    {
    case ORC_STANDING:
    {
        if (observer->canSeePlayer && move->state == MOVE_STILL)
        {
            Direction dir = PointToward(PointFromVector(body->pos), observer->playerPos);
            MoveStart(body, move, dir);
            orc->state = ORC_STEPPING;
        }
    }
    break;

    case ORC_STEPPING:
    {
        if (move->state == MOVE_STILL)
        {
            orc->state = ORC_STANDING;
        }
    }
    break;
    }
}