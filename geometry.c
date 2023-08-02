#include <geometry.h>

const Vector3 DIRECTION_VECTORS[4] = {
    (Vector3){0, 0, 1},  // North
    (Vector3){0, 0, -1}, // South
    (Vector3){1, 0, 0},  // East
    (Vector3){-1, 0, 0}  // West
};

const Direction DIRECTION_RIGHTS[4] = {
    EAST,
    WEST,
    SOUTH,
    NORTH,
};

const Direction DIRECTION_LEFTS[4] = {
    WEST,
    EAST,
    NORTH,
    SOUTH,
};

const Direction DIRECTION_REVERSES[4] = {
    SOUTH,
    NORTH,
    WEST,
    EAST,
};

Vector3
DirectionVector(Direction dir)
{
    return DIRECTION_VECTORS[dir];
}

Direction DirectionFace(Direction dir, RelativeDirection rel)
{
    switch (rel)
    {
    case FORWARD:
        return dir;
    case BACK:
        return DIRECTION_REVERSES[dir];
    case LEFT:
        return DIRECTION_LEFTS[dir];
    case RIGHT:
        return DIRECTION_RIGHTS[dir];
    }
}

bool PointEqual(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

Point PointAdd(Point p1, Point p2)
{
    return (Point){p1.x + p2.x, p1.y + p2.y};
}

Vector3 PointToVector(Point p)
{
    return (Vector3){p.x * TILE_SIZE, 0, p.y * TILE_SIZE};
}

Point PointFromVector(Vector3 v)
{
    return (Point){v.x / TILE_SIZE, v.z / TILE_SIZE};
}