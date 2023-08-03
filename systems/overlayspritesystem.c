#include <overlayspritesystem.h>
#include <textures.h>

void OverlaySpriteSystem(OverlaySprite *sprites)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        OverlaySprite *sprite = &sprites[i];
        if (!sprite->valid)
            continue;

        DrawTextureEx(PlayerAttackTexture, (Vector2){100.0, 50.0}, 0.0, 12.0, WHITE);
    }
}