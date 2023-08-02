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

    switch (player->state)
    {
    case PLAYER_STANDING:
    {
        if (IsKeyDown(KEY_W))
        {
            MoveStart(body, move, DirectionFace(player->facing, FORWARD));
            player->state = PLAYER_STEPPING;
        }
        else if (IsKeyDown(KEY_S))
        {
            MoveStart(body, move, DirectionFace(player->facing, BACK));
            player->state = PLAYER_STEPPING;
        }
        else if (IsKeyDown(KEY_Q))
        {
            MoveStart(body, move, DirectionFace(player->facing, RIGHT));
            player->state = PLAYER_STEPPING;
        }
        else if (IsKeyDown(KEY_E))
        {
            MoveStart(body, move, DirectionFace(player->facing, LEFT));
            player->state = PLAYER_STEPPING;
        }
    }
    break;

    case PLAYER_STEPPING:
    {
        if (move->state == MOVE_STILL)
            player->state = PLAYER_STANDING;
    }
    break;
    }

    PlayerUpdateCamera(bodies, player, camera);
}

void PlayerUpdateCamera(Body *body, Player *player, Camera3D *camera)
{
    camera->position = body->pos;
    camera->target = Vector3Add(camera->position, DirectionVector(player->facing));
}