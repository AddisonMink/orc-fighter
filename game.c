#include <game.h>
#include <raymath.h>

const Point GAME_PLAYER_POINT = {5, 5};
const int MAX_LEVEL = 3;

const Point ORC_POINTS[3][3] = {
    {{5, 8}, {-1, -1}, {-1, -1}},
    {{4, 8}, {6, 8}, {-1, -1}},
    {{4, 8}, {6, 8}, {5, 1}}};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const int TITLE_FONT_SIZE = 32;
const int SUBTITLE_FONT_SIZE = 16;

void GameDrawTitle(const char *title)
{
    int width = MeasureText(title, TITLE_FONT_SIZE);
    int x = SCREEN_WIDTH / 2 - width / 2;
    int y = SCREEN_HEIGHT / 2 - TITLE_FONT_SIZE;
    DrawText(title, x, y, TITLE_FONT_SIZE, RAYWHITE);
}

void GameDrawSubtitle(const char *subtitle)
{
    int width = MeasureText(subtitle, SUBTITLE_FONT_SIZE);
    int x = SCREEN_WIDTH / 2 - width / 2;
    int y = SCREEN_HEIGHT / 2 + SUBTITLE_FONT_SIZE;
    DrawText(subtitle, x, y, SUBTITLE_FONT_SIZE, RAYWHITE);
}

void GameInit(Game *game, Camera3D *camera, int level)
{
    game->state = GAME_STARTING;
    game->level = level;
    WorldInit(&game->world);
    WorldAddPlayer(&game->world, camera, GAME_PLAYER_POINT);

    for (int i = 0; i < level; i++)
    {
        Point point = ORC_POINTS[level - 1][i];
        WorldAddOrc(&game->world, point);
    }

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

        bool playerDead = !game->world.valids[PLAYER_ID];

        bool orcsDead = true;
        for (int i = 0; i < NUM_ENTITIES; i++)
        {
            if (game->world.orcs[i].valid)
            {
                orcsDead = false;
                break;
            }
        }

        if (playerDead)
        {
            game->state = GAME_OVER;
        }
        else if (orcsDead)
        {
            game->state = GAME_LEVEL_COMPLETE;
        }
    }
    break;

    case GAME_OVER:
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            GameInit(game, camera, 1);
            game->state = GAME_STARTING;
        }
    }
    break;

    case GAME_LEVEL_COMPLETE:
    {
        if (IsKeyPressed(KEY_SPACE) && game->level < MAX_LEVEL)
        {
            int level = game->level < MAX_LEVEL ? game->level + 1 : 1;
            GameInit(game, camera, level);
            game->state = GAME_STARTING;
        }
    }
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
        if (game->level == 1)
            GameDrawTitle("O R C  F I G H T E R");
        else
            GameDrawTitle(TextFormat("LEVEL %d", game->level));
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

    case GAME_LEVEL_COMPLETE:
    {
        if (game->level < MAX_LEVEL)
        {
            GameDrawTitle("LEVEL COMPLETE!");
            GameDrawSubtitle("Press 'SPACE' to continue.");
        }
        else
        {
            GameDrawTitle("G A M E  C O M P L E T E");
            GameDrawSubtitle("Presss 'SPACE' to restart.");
        }
    }
    }
}
