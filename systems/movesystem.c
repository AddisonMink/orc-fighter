#include <movesystem.h>
#include <raymath.h>

#define TOLERANCE 0.1

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
        if (move->valid && body->valid)
            MoveUpdate(bodies, move, delta);
    }
}

void MoveUpdate(Body *body, Move *move, float delta)
{
    switch (move->state)
    {
    case MOVE_STILL:
        break;

    case MOVE_MOVING:
    {
        Vector3 vector = Vector3Scale(DirectionVector(move->dir), move->speed * delta);
        body->pos = Vector3Add(body->pos, vector);
        if (Vector3Distance(body->pos, move->dest) <= TOLERANCE)
        {
            body->pos = move->dest;
            move->state = MOVE_STILL;
        }
    }
    break;
    }
}