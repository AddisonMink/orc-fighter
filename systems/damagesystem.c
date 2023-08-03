#include <damagesystem.h>

void DamageSystem(World *world, Body *bodies, Hurtbox *hurtboxes, Defence *defences)
{
    for (int i = 0; i < NUM_ENTITIES; i++)
    {
        Hurtbox *hurtbox = &hurtboxes[i];
        Body *body = &bodies[i];
        if (!hurtbox->valid || !body->valid)
            continue;

        Point hurtboxPoint = PointFromVector(body->pos);

        for (int j = 0; j < NUM_ENTITIES; j++)
        {
            Defence *defence = &defences[j];
            Body *dbody = &bodies[j];
            if (!defence->valid || !dbody->valid)
                continue;

            if (PointEqual(hurtboxPoint, PointFromVector(dbody->pos)))
                WorldClearEntity(world, j);
        }

        hurtbox->valid = false;
    }
}