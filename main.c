#include <raylib.h>
#include <components.h>
#include <textures.h>
#include <game.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Orc Fighter!");

    PlayerAttackTexture = LoadTexture("resources/player-attack.png");
    MonstersTexture = LoadTexture("resources/monsters.png");

    Camera3D camera = {0};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Game game;
    GameInit(&game, &camera, 1);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        GameUpdate(&game, &camera, GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        GameDraw3D(&game, &camera);
        EndMode3D();
        GameDraw2D(&game);
        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(PlayerAttackTexture);
    UnloadTexture(MonstersTexture);
    return 0;
}