#include <drawhudsystem.h>

void DrawHudSystem(Player *players)
{
    Player *player = &players[PLAYER_ID];

    DrawText("ATTACK", 10, 10, 16, RAYWHITE);
    if (player->attackCooldown <= 0)
        DrawText("READY", 90, 10, 16, GREEN);
    else
        DrawText("ON COOLDOWN", 90, 10, 16, RED);
}