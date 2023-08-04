#ifndef GAME_H
#define GAME_H

#include <components.h>

typedef enum GameState
{
    GAME_STARTING,
    GAME_RUNNING,
    GAME_OVER,
} GameState;

typedef struct Game
{
    GameState state;
    World world;
} Game;

void GameInit(Game *game, Camera3D *camera);

void GameUpdate(Game *game, Camera3D *camera, float delta);

void GameDraw3D(Game *game, Camera3D *camera);

void GameDraw2D(Game *game);

#endif