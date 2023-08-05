#ifndef GAME_H
#define GAME_H

#include <components.h>

typedef enum GameState
{
    GAME_STARTING,
    GAME_RUNNING,
    GAME_OVER,
    GAME_LEVEL_COMPLETE,
} GameState;

typedef struct Game
{
    GameState state;
    int level;
    World world;
} Game;

void GameInit(Game *game, Camera3D *camera, int level);

void GameUpdate(Game *game, Camera3D *camera, float delta);

void GameDraw3D(Game *game, Camera3D *camera);

void GameDraw2D(Game *game);

#endif