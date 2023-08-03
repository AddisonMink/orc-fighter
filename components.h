#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <geometry.h>

#define NUM_ENTITIES 10
#define PLAYER_ID 0

typedef int Id;

// Component
typedef struct Body
{
    Id id;
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
    Id id;
    bool valid;
    MoveState state;
    float speed;
    float cooldown;
    float cooldownTimer;
    Direction dir;
    Point dest;
} Move;

void MoveInit(Move *move, float speed, float cooldown);
void MoveStart(Body *body, Move *move, Direction dir);

// Component
typedef struct Draw
{
    Id id;
    bool valid;
    Texture2D texture;
    Rectangle frame;
} Draw;

void DrawInit(Draw *draw, Texture2D texture, Rectangle frame);

// Component
typedef struct Observer
{
    Id id;
    bool valid;
    bool canSeePlayer;
    Point playerPos;
} Observer;

void ObserverInit(Observer *observer);

// Component
typedef struct OverlaySprite
{
    Id id;
    bool valid;
} OverlaySprite;

void OverlaySpriteInit(OverlaySprite *sprite);

// Component
typedef struct Defence
{
    Id id;
    bool valid;
} Defence;

void DefenceInit(Defence *defence);

typedef enum HurtboxLayer
{
    HURTBOX_PLAYER,
    HURTBOX_ENEMY,
} HurtboxLayer;

// Component
typedef struct Hurtbox
{
    Id id;
    bool valid;
    HurtboxLayer layer;
} Hurtbox;

void HurtboxInit(Hurtbox *hurtbox, HurtboxLayer layer);

typedef enum PlayerState
{
    PLAYER_STANDING,
    PLAYER_STEPPING,
    PLAYER_TURNING,
    PLAYER_ATTACKING,
} PlayerState;

// Component
typedef struct Player
{
    Id id;
    bool valid;
    PlayerState state;
    Direction facing;
    RelativeDirection turningDir;
    float attackCooldown;
    float turningProgress;
    float attackingTimer;
    Id attackingId;
} Player;

void PlayerInit(Player *player);

typedef enum OrcState
{
    ORC_STANDING,
    ORC_STEPPING,
    ORC_WINDING_UP,
    ORC_ATTACKING,
} OrcState;

// Component
typedef struct Orc
{
    Id id;
    bool valid;
    OrcState state;
    float attackCooldown;
    float windingUpTimer;
    float attackingTimer;
} Orc;

void OrcInit(Orc *orc);

typedef struct World
{
    bool valids[NUM_ENTITIES];
    Body bodies[NUM_ENTITIES];
    Move moves[NUM_ENTITIES];
    Draw draws[NUM_ENTITIES];
    Observer observers[NUM_ENTITIES];
    OverlaySprite overlaySprites[NUM_ENTITIES];
    Defence defences[NUM_ENTITIES];
    Hurtbox hurtboxes[NUM_ENTITIES];
    Player players[NUM_ENTITIES];
    Orc orcs[NUM_ENTITIES];
} World;

void WorldInit(World *world);

void WorldRunSystems(
    World *world,
    Camera3D *camera,
    float delta);

void WorldRunDraw3DSystems(World *world, Camera3D *camera);

void WorldRunDraw2DSystems(World *world);

void WorldClearEntity(World *world, Id id);

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p);

Id WorldAddPlayerAttack(
    World *world,
    Point p);

Id WorldAddOrc(
    World *world,
    Point p);

#endif