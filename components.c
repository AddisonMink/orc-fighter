#include <components.h>
#include <raymath.h>
#include <drawsystem.h>
#include <movesystem.h>
#include <observersystem.h>
#include <orcsystem.h>
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
    move->dest = PointAddDirection(PointFromVector(body->pos), dir);
    move->state = MOVE_STARTING;
}

void DrawInit(Draw *draw, Color color)
{
    draw->valid = true;
    draw->color = color;
}

void ObserverInit(Observer *observer)
{
    observer->valid = true;
    observer->canSeePlayer = false;
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
    orc->state = ORC_STANDING;
}

void WorldInit(World *world)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        world->valids[i] = false;

        world->bodies[i].id = i;
        world->bodies[i].valid = false;

        world->moves[i].id = i;
        world->moves[i].valid = false;

        world->draws[i].id = i;
        world->draws[i].valid = false;

        world->observers[i].id = i;
        world->observers[i].valid = false;

        world->players[i].id = i;
        world->players[i].valid = false;

        world->orcs[i].id = i;
        world->orcs[i].valid = false;
    }
}

void WorldRunSystems(
    World *world,
    Camera3D *camera,
    float delta)
{
    ObserverSystem(world->bodies, world->observers, world->players);
    PlayerSystem(world->bodies, world->moves, world->players, camera, delta);
    OrcSystem(world->bodies, world->moves, world->observers, world->orcs);
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
            world->valids[i] = true;
            id = i;
            break;
        }

    if (id < 1)
        return -1;

    const float moveSpeed = 0.5;

    BodyInit(&world->bodies[id], p);
    MoveInit(&world->moves[id], moveSpeed);
    DrawInit(&world->draws[id], DARKGREEN);
    ObserverInit(&world->observers[id]);
    OrcInit(&world->orcs[id]);
    return id;
}