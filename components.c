#include <components.h>
#include <raymath.h>
#include <playersystem.h>
#include <movesystem.h>

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
    move->dest = Vector3Add(body->pos, Vector3Scale(DirectionVector(dir), TILE_SIZE));
    move->state = MOVE_MOVING;
}

void PlayerInit(Player *player)
{
    player->valid = true;
    player->state = PLAYER_STANDING;
    player->facing = NORTH;
}

void WorldInit(World *world)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        world->bodies[i].valid = false;
        world->moves[i].valid = false;
        world->players[i].valid = false;
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

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p)
{
    const float moveSpeed = 5.0;

    BodyInit(&world->bodies[PLAYER_ID], p);
    MoveInit(&world->moves[PLAYER_ID], moveSpeed);
    PlayerInit(&world->players[PLAYER_ID]);
}