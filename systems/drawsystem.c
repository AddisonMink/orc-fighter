#include <drawsystem.h>

void DrawSystem(
    Body *bodies,
    Draw *draws)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Body *body = &bodies[i];
        Draw *draw = &draws[i];
        if (draw->valid && body->valid)
        {
            DrawCube(body->pos, TILE_SIZE, TILE_SIZE, TILE_SIZE, draw->color);
        }
    }
}