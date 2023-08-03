#include <geometry.h>
#include <raymath.h>
#include <stdlib.h>

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

const Point DIRECTION_POINTS[4] = {
    (Point){0, 1},
    (Point){0, -1},
    (Point){1, 0},
    (Point){-1, 0},
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

Vector3 DirectionTurnToward(Direction d, RelativeDirection dir, float fraction)
{
    Vector3 from = DirectionVector(d);
    Vector3 to = DirectionVector(DirectionFace(d, dir));

    return Vector3Normalize(Vector3Add(
        Vector3Scale(from, 1 - fraction),
        Vector3Scale(to, fraction)));
}

bool PointEqual(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

Point PointAdd(Point p1, Point p2)
{
    return (Point){p1.x + p2.x, p1.y + p2.y};
}

Point PointSubtract(Point p1, Point p2)
{
    return (Point){p2.x - p1.x, p2.y - p1.y};
}

Direction PointToward(Point p1, Point p2)
{
    Direction dir;
    Point diff = PointSubtract(p1, p2);
    if (abs(diff.x) >= abs(diff.y))
        dir = diff.x > 0 ? EAST : WEST;
    else
        dir = diff.y > 0 ? NORTH : SOUTH;
    return dir;
}

Point PointAddDirection(Point p, Direction dir)
{
    return PointAdd(p, DIRECTION_POINTS[dir]);
}

float PointDistance(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

Vector3 PointToVector(Point p)
{
    return (Vector3){p.x * TILE_SIZE, 0, p.y * TILE_SIZE};
}

Point PointFromVector(Vector3 v)
{
    return (Point){v.x / TILE_SIZE, v.z / TILE_SIZE};
}