#include <playersystem.h>
#include <raymath.h>

#define PLAYER_TURNING_SPEED PI

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

    Point p = PointFromVector(body->pos);

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
        else if (IsKeyPressed(KEY_D))
        {
            player->turningDir = LEFT;
            player->turningProgress = 0;
            player->state = PLAYER_TURNING;
        }
        else if (IsKeyPressed(KEY_A))
        {
            player->turningDir = RIGHT;
            player->turningProgress = 0;
            player->state = PLAYER_TURNING;
        }
        PlayerUpdateCamera(bodies, player, camera);
    }
    break;

    case PLAYER_STEPPING:
    {
        PlayerUpdateCamera(bodies, player, camera);
        if (move->state == MOVE_STILL)
            player->state = PLAYER_STANDING;
    }
    break;

    case PLAYER_TURNING:
    {
        player->turningProgress += PLAYER_TURNING_SPEED * delta;
        Vector3 vector = DirectionTurnToward(player->facing, player->turningDir, player->turningProgress);
        camera->target = Vector3Add(camera->position, vector);

        if (player->turningProgress >= 1)
        {
            player->facing = DirectionFace(player->facing, player->turningDir);
            player->state = PLAYER_STANDING;
            PlayerUpdateCamera(body, player, camera);
        }
    }
    }
}

void PlayerUpdateCamera(Body *body, Player *player, Camera3D *camera)
{
    camera->position = body->pos;
    camera->target = Vector3Add(camera->position, DirectionVector(player->facing));
}