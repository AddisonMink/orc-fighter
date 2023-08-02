#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <geometry.h>

#define NUM_ENTITIES 10
#define PLAYER_ID 0

// Component
typedef struct Body
{
    bool valid;
    Vector3 pos;
} Body;

void BodyInit(Body *body, Point p);

typedef enum MoveState
{
    MOVE_STILL,
    MOVE_MOVING
} MoveState;

// Component
typedef struct Move
{
    bool valid;
    MoveState state;
    float speed;
    Direction dir;
    Vector3 dest;
} Move;

void MoveInit(Move *move, float speed);
void MoveStart(Body *body, Move *move, Direction dir);


typedef enum PlayerState
{
    PLAYER_STANDING,
    PLAYER_STEPPING,
} PlayerState;

// Component
typedef struct Player
{
    bool valid;
    PlayerState state;
    Direction facing;
} Player;

void PlayerInit(Player *player);

typedef struct World
{
    Body bodies[NUM_ENTITIES];
    Move moves[NUM_ENTITIES];
    Player players[NUM_ENTITIES];
} World;

void WorldInit(World *world);

void WorldRunSystems(
    World *world,
    Camera3D *camera,
    float delta);

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p);

#endif