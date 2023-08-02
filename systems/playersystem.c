#include <playersystem.h>
#include <raymath.h>

void PlayerUpdateCamera(Body *body, Player *player, Camera3D *camera);

void PlayerSystem(
    Body *bodies,
    Move *moves,
    Player *players,
    Camera3D *camera,
    float delta)
{
    Body *body = &bodies[PLAYER_ID];
    Move *move = &moves[PLAYER_ID];
    Player *player = &players[PLAYER_ID];

    PlayerUpdateCamera(bodies, player, camera);
}

void PlayerUpdateCamera(Body *body, Player *player, Camera3D *camera)
{
    camera->position = body->pos;
    camera->target = Vector3Add(camera->position, DirectionVector(player->facing));
}