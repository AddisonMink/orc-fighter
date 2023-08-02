#include <geometry.h>

const Vector3 DIRECTION_VECTORS[4] = {
    (Vector3){0, 0, 1},  // North
    (Vector3){0, 0, -1}, // South
    (Vector3){1, 0, 0},  // East
    (Vector3){-1, 0, 0}  // West
};

Vector3 DirectionVector(Direction dir)
{
    return DIRECTION_VECTORS[dir];
}

Vector3 PointToVector(Point p)
{
    return (Vector3){p.x * TILE_SIZE, 0, p.y * TILE_SIZE};
}

Point PointFromVector(Vector3 v)
{
    return (Point){v.x / TILE_SIZE, v.z / TILE_SIZE};
}