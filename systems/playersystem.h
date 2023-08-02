#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include <components.h>

void PlayerSystem(
    Body *bodies,
    Move *moves,
    Player *players,
    Camera3D *camera,
    float delta);

#endif