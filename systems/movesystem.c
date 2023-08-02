#include <movesystem.h>
#include <raymath.h>

#define TOLERANCE 0.1

bool MoveIsBlocked(Body *bodies, Move *moves, int id, Point pos);
void MoveUpdate(Body *body, Move *move, float delta);

void MoveSystem(
    Body *bodies,
    Move *moves,
    float delta)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Body *body = &bodies[i];
        Move *move = &moves[i];
        if (!move->valid || !body->valid)
            continue;

        if (move->state == MOVE_STARTING && MoveIsBlocked(bodies, moves, i, move->dest))
        {
            move->state = MOVE_STILL;
            continue;
        }

        MoveUpdate(bodies, move, delta);
    }
}

bool MoveIsBlocked(Body *bodies, Move *moves, int id, Point pos)
{
    bool blocked = false;

    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        if (i == id)
            continue;

        Body *body = &bodies[i];
        if (body->valid && PointEqual(pos, PointFromVector(body->pos)))
        {
            blocked = true;
            break;
        }

        Move *move = &moves[i];
        if (move->valid && move->state == MOVE_MOVING && PointEqual(pos, move->dest))
        {
            blocked = true;
            break;
        }
    }

    return blocked;
}

void MoveUpdate(Body *body, Move *move, float delta)
{
    switch (move->state)
    {
    case MOVE_STILL:
        break;

    case MOVE_STARTING:
    {
        move->state = MOVE_MOVING;
        MoveUpdate(body, move, delta);
    }
    break;

    case MOVE_MOVING:
    {
        Vector3 vector = Vector3Scale(DirectionVector(move->dir), move->speed * delta);
        body->pos = Vector3Add(body->pos, vector);
        if (Vector3Distance(body->pos, PointToVector(move->dest)) <= TOLERANCE)
        {
            body->pos = PointToVector(move->dest);
            move->state = MOVE_STILL;
        }
    }
    break;
    }
}