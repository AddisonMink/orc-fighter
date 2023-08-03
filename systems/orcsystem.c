#include <orcsystem.h>
#include <textures.h>

#define ORC_WINDUP_DURATION 0.2
#define ORC_ATTACK_DURATION 0.2
#define ORC_ATTACK_COOLDOWN 1.0

void OrcUpdate(
    Body *body,
    Move *move,
    Draw *draw,
    Observer *observer,
    Orc *orc,
    float delta);

void OrcSystem(
    Body *bodies,
    Move *moves,
    Draw *draws,
    Observer *observers,
    Orc *orcs,
    float delta)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        if (!orcs[i].valid)
            continue;

        Body *body = &bodies[i];
        Move *move = &moves[i];
        Draw *draw = &draws[i];
        Observer *oberver = &observers[i];
        Orc *orc = &orcs[i];
        OrcUpdate(body, move, draw, oberver, orc, delta);
    }
}

void OrcUpdate(
    Body *body,
    Move *move,
    Draw *draw,
    Observer *observer,
    Orc *orc,
    float delta)
{
    switch (orc->state)
    {
    case ORC_STANDING:
    {
        if (orc->attackCooldown >= 0)
            orc->attackCooldown -= delta;

        if (!observer->canSeePlayer)
            return;

        bool adjacent = PointDistance(PointFromVector(body->pos), observer->playerPos) == 1;
        if (adjacent && orc->attackCooldown <= 0)
        {
            draw->frame = ORC_WINDUP_FRAME;
            orc->windingUpTimer = ORC_WINDUP_DURATION;
            orc->state = ORC_WINDING_UP;
        }
        else if (move->state == MOVE_STILL)
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

    case ORC_WINDING_UP:
    {
        orc->windingUpTimer -= delta;
        if (orc->windingUpTimer <= 0)
        {
            draw->frame = ORC_ATTACK_FRAME;
            orc->attackingTimer = ORC_ATTACK_DURATION;
            orc->state = ORC_ATTACKING;
        }
    }
    break;

    case ORC_ATTACKING:
    {
        orc->attackingTimer -= delta;
        if (orc->attackingTimer <= 0)
        {
            draw->frame = ORC_STANDING_FRAME;
            orc->attackCooldown = ORC_ATTACK_COOLDOWN;
            orc->state = ORC_STANDING;
        }
    }
    break;
    }
}