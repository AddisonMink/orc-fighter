#include <raylib.h>
#include <components.h>
#include <textures.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Orc Fighter!");

    PlayerAttackTexture = LoadTexture("resources/player-attack.png");

    Camera3D camera = {0};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    World world;
    WorldInit(&world);
    WorldAddPlayer(&world, &camera, (Point){10, 7});
    WorldAddOrc(&world, (Point){5, 8});

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        WorldRunSystems(&world, &camera, GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        WorldRunDraw3DSystems(&world);
        EndMode3D();

        WorldRunDraw2DSystems(&world);
        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(PlayerAttackTexture);
    return 0;
}