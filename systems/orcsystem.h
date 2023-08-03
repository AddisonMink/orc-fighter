#ifndef ORC_SYSTEM_H
#define ORC_SYSTEM_H

#include <components.h>

void OrcSystem(
    World *world,
    Body *bodies,
    Move *moves,
    Draw *draws,
    Observer *observers,
    Orc *orcs,
    float delta);

#endif