#include <components.h>
#include <raymath.h>
#include <drawhudsystem.h>
#include <drawsystem.h>
#include <movesystem.h>
#include <observersystem.h>
#include <orcsystem.h>
#include <overlayspritesystem.h>
#include <playersystem.h>
#include <textures.h>
#include <damagesystem.h>

void BodyInit(Body *body, Point p)
{
    body->valid = true;
    body->pos = PointToVector(p);
}

void MoveInit(Move *move, float speed, float cooldown)
{
    move->valid = true;
    move->speed = speed;
    move->cooldown = cooldown;
    move->cooldownTimer = 0;
    move->state = MOVE_STILL;
}

void MoveStart(Body *body, Move *move, Direction dir)
{
    if (move->cooldownTimer > 0)
        return;
    move->dir = dir;
    move->dest = PointAddDirection(PointFromVector(body->pos), dir);
    move->state = MOVE_STARTING;
}

void DrawInit(Draw *draw, Texture2D texture, Rectangle frame)
{
    draw->valid = true;
    draw->texture = texture;
    draw->frame = frame;
}

void ObserverInit(Observer *observer)
{
    observer->valid = true;
    observer->canSeePlayer = false;
}

void OverlaySpriteInit(OverlaySprite *sprite)
{
    sprite->valid = true;
}

void DefenceInit(Defence *defence)
{
    defence->valid = true;
}

void HurtboxInit(Hurtbox *hurtbox, HurtboxLayer layer)
{
    hurtbox->valid = true;
    hurtbox->layer = layer;
}

void PlayerInit(Player *player)
{
    player->valid = true;
    player->state = PLAYER_STANDING;
    player->facing = NORTH;
    player->attackCooldown = 0;
}

void OrcInit(Orc *orc)
{
    orc->valid = true;
    orc->state = ORC_STANDING;
    orc->attackCooldown = 0;
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

        world->overlaySprites[i].id = i;
        world->overlaySprites[i].valid = false;

        world->defences[i].id = i;
        world->defences[i].valid = false;

        world->hurtboxes[i].id = i;
        world->hurtboxes[i].valid = false;

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
    PlayerSystem(world, world->bodies, world->moves, world->players, camera, delta);
    OrcSystem(world, world->bodies, world->moves, world->draws, world->observers, world->orcs, delta);
    MoveSystem(world->bodies, world->moves, delta);
    DamageSystem(world, world->bodies, world->hurtboxes, world->defences);
}

void WorldRunDraw3DSystems(World *world, Camera3D *camera)
{
    DrawSystem(world->bodies, world->draws, camera);
}

void WorldRunDraw2DSystems(World *world)
{
    OverlaySpriteSystem(world->overlaySprites);
    DrawHudSystem(world->players);
}

void WorldClearEntity(World *world, Id id)
{
    world->valids[id] = false;
    world->bodies[id].valid = false;
    world->moves[id].valid = false;
    world->draws[id].valid = false;
    world->observers[id].valid = false;
    world->overlaySprites[id].valid = false;
    world->defences[id].valid = false;
    world->hurtboxes[id].valid = false;
    world->orcs[id].valid = false;
    world->players[id].valid = false;
}

Id WorldInitEntity(World *world)
{
    Id id = -1;
    for (int i = 1; i < NUM_ENTITIES; i++)
        if (!world->valids[i])
        {
            world->valids[i] = true;
            id = i;
            break;
        }

    return id;
}

void WorldAddPlayer(
    World *world,
    Camera3D *camera,
    Point p)
{
    const float moveSpeed = 5.0;
    const float mvoeCooldown = 0.1;

    world->valids[PLAYER_ID] = true;
    BodyInit(&world->bodies[PLAYER_ID], p);
    MoveInit(&world->moves[PLAYER_ID], moveSpeed, mvoeCooldown);
    DefenceInit(&world->defences[PLAYER_ID]);
    PlayerInit(&world->players[PLAYER_ID]);
}

Id WorldAddPlayerAttack(
    World *world,
    Point p)
{
    Id id = WorldInitEntity(world);
    if (id < 0)
        return id;

    BodyInit(&world->bodies[id], p);
    OverlaySpriteInit(&world->overlaySprites[id]);
    HurtboxInit(&world->hurtboxes[id], HURTBOX_ENEMY);
    return id;
}

Id WorldAddOrc(
    World *world,
    Point p)
{
    int id = WorldInitEntity(world);
    if (id < 0)
        return id;

    const float moveSpeed = 2.5;
    const float moveCooldown = 0.1;

    BodyInit(&world->bodies[id], p);
    MoveInit(&world->moves[id], moveSpeed, moveCooldown);
    DrawInit(&world->draws[id], MonstersTexture, ORC_STANDING_FRAME);
    ObserverInit(&world->observers[id]);
    DefenceInit(&world->defences[id]);
    OrcInit(&world->orcs[id]);
    return id;
}

Id WorldAddOrcAttack(
    World *world,
    Point p)
{
    Id id = WorldInitEntity(world);
    if (id < 0)
        return id;

    BodyInit(&world->bodies[id], p);
    HurtboxInit(&world->hurtboxes[id], HURTBOX_PLAYER);
    return id;
}