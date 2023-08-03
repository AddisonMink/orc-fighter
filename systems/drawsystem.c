#include <drawsystem.h>

void DrawSystem(
    Body *bodies,
    Draw *draws,
    Camera3D *camera)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Body *body = &bodies[i];
        Draw *draw = &draws[i];
        if (draw->valid && body->valid)
        {
            DrawBillboardRec(*camera, draw->texture, draw->frame, body->pos, (Vector2){TILE_SIZE, TILE_SIZE}, WHITE);
        }
    }
}