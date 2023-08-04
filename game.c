#include <game.h>
#include <raymath.h>

const Point GAME_PLAYER_POINT = {5, 1};
const Point GAME_ORC_POINT = {5, 8};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const int TITLE_FONT_SIZE = 32;
const int SUBTITLE_FONT_SIZE = 16;

void GameDrawTitle(char *title)
{
    int width = MeasureText(title, TITLE_FONT_SIZE);
    int x = SCREEN_WIDTH / 2 - width / 2;
    int y = SCREEN_HEIGHT / 2 - TITLE_FONT_SIZE;
    DrawText(title, x, y, TITLE_FONT_SIZE, RAYWHITE);
}

void GameDrawSubtitle(char *subtitle)
{
    int width = MeasureText(subtitle, SUBTITLE_FONT_SIZE);
    int x = SCREEN_WIDTH / 2 - width / 2;
    int y = SCREEN_HEIGHT / 2 + SUBTITLE_FONT_SIZE;
    DrawText(subtitle, x, y, SUBTITLE_FONT_SIZE, RAYWHITE);
}

void GameInit(Game *game, Camera3D *camera)
{
    game->state = GAME_STARTING;
    WorldInit(&game->world);
    WorldAddPlayer(&game->world, camera, GAME_PLAYER_POINT);
    WorldAddOrc(&game->world, GAME_ORC_POINT);

    Vector3 playerPos = game->world.bodies[PLAYER_ID].pos;
    Vector3 facingVector = DirectionVector(game->world.players[PLAYER_ID].facing);
    camera->position = playerPos;
    camera->target = Vector3Add(playerPos, facingVector);
}

void GameUpdate(Game *game, Camera3D *camera, float delta)
{
    switch (game->state)
    {
    case GAME_STARTING:
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            game->state = GAME_RUNNING;
        }
    }
    break;

    case GAME_RUNNING:
    {
        WorldRunSystems(&game->world, camera, delta);
        if (!game->world.valids[PLAYER_ID])
        {
            game->state = GAME_OVER;
        }
    }
    break;

    case GAME_OVER:
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            GameInit(game, camera);
            game->state = GAME_STARTING;
        }
    }
    break;
    }
}

void GameDraw3D(Game *game, Camera3D *camera)
{
    WorldRunDraw3DSystems(&game->world, camera);
}

void GameDraw2D(Game *game)
{
    switch (game->state)
    {
    case GAME_STARTING:
    {
        GameDrawTitle("O R C  F I G H T E R");
        GameDrawSubtitle("Press 'SPACE' to start.");
    }
    break;

    case GAME_RUNNING:
    {
        WorldRunDraw2DSystems(&game->world);
    }
    break;

    case GAME_OVER:
    {
        GameDrawTitle("G A M E  O V E R");
        GameDrawSubtitle("Press 'SPACE' to restart.");
    }
    break;
    }
}
