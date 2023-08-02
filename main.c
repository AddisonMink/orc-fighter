#include <raylib.h>
#include <components.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Orc Fighter!");

    Camera3D camera = {0};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    World world;
    WorldInit(&world);
    WorldAddPlayer(&world, &camera, (Point){5, 5});
    MoveStart(&world.bodies[PLAYER_ID], &world.moves[PLAYER_ID], NORTH);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        WorldRunSystems(&world, &camera, GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawCube((Vector3){5, 0, 8}, 1, 1, 1, RED);
        DrawCubeWires((Vector3){5, 0, 8}, 1, 1, 1, MAROON);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}