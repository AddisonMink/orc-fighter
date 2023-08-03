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
    MOVE_STARTING,
    MOVE_MOVING
} MoveState;

// Component
typedef struct Move
{
    bool valid;
    MoveState state;
    float speed;
    Direction dir;
    Point dest;
} Move;

void MoveInit(Move *move, float speed);
void MoveStart(Body *body, Move *move, Direction dir);

// Component
typedef struct Draw
{
    bool valid;
    Color color;
} Draw;

void DrawInit(Draw *draw, Color color);

typedef enum PlayerState
{
    PLAYER_STANDING,
    PLAYER_STEPPING,
    PLAYER_TURNING,
} PlayerState;

// Component
typedef struct Player
{
    bool valid;
    PlayerState state;
    Direction facing;
    RelativeDirection turningDir;
    float turningProgress;
} Player;

void PlayerInit(Player *player);

// Component
typedef struct Orc
{
    bool valid;
} Orc;

void OrcInit(Orc *orc);

typedef struct World
{
    bool valids[NUM_ENTITIES];
    Body bodies[NUM_ENTITIES];
    Move moves[NUM_ENTITIES];
    Draw draws[NUM_ENTITIES];
    Player players[NUM_ENTITIES];
    Orc orcs[NUM_ENTITIES];
} World;

void WorldInit(World *world);

void WorldRunSystems(
    World *world,
    Camera3D *camera,
    float delta);

void WorldRunDraw3DSystems(
    World *world);

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p);

int WorldAddOrc(
    World *world,
    Point p);

#endif