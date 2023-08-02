#include <components.h>
#include <raymath.h>
#include <drawsystem.h>
#include <movesystem.h>
#include <playersystem.h>

void BodyInit(Body *body, Point p)
{
    body->valid = true;
    body->pos = PointToVector(p);
}

void MoveInit(Move *move, float speed)
{
    move->valid = true;
    move->speed = speed;
    move->state = MOVE_STILL;
}

void MoveStart(Body *body, Move *move, Direction dir)
{
    move->dir = dir;
    move->dest = PointAdd(PointFromVector(body->pos), PointFromVector(DirectionVector(dir)));
    move->state = MOVE_STARTING;
}

void DrawInit(Draw *draw, Color color)
{
    draw->valid = true;
    draw->color = color;
}

void PlayerInit(Player *player)
{
    player->valid = true;
    player->state = PLAYER_STANDING;
    player->facing = NORTH;
}

void OrcInit(Orc *orc)
{
    orc->valid = true;
}

void WorldInit(World *world)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        world->valids[i] = false;
        world->bodies[i].valid = false;
        world->moves[i].valid = false;
        world->draws[i].valid = false;
        world->players[i].valid = false;
        world->orcs[i].valid = false;
    }
}

void WorldRunSystems(
    World *world,
    Camera3D *camera,
    float delta)
{
    PlayerSystem(world->bodies, world->moves, world->players, camera, delta);
    MoveSystem(world->bodies, world->moves, delta);
}

void WorldRunDraw3DSystems(
    World *world)
{
    DrawSystem(world->bodies, world->draws);
}

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p)
{
    const float moveSpeed = 5.0;

    world->valids[PLAYER_ID] = true;
    BodyInit(&world->bodies[PLAYER_ID], p);
    MoveInit(&world->moves[PLAYER_ID], moveSpeed);
    PlayerInit(&world->players[PLAYER_ID]);
}

int WorldAddOrc(
    World *world,
    Point p)
{
    int id = -1;
    for (int i = 1; i < NUM_ENTITIES; i++)
        if (!world->valids[i])
        {
            id = i;
            break;
        }

    if (id < 1)
        return -1;

    const float moveSpeed = 0.5;

    BodyInit(&world->bodies[id], p);
    MoveInit(&world->moves[id], moveSpeed);
    DrawInit(&world->draws[id], DARKGREEN);
    OrcInit(&world->orcs[id]);
    return id;
}