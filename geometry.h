#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <raylib.h>

#define TILE_SIZE 1

typedef enum Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef enum RelativeDirection
{
    FORWARD,
    BACK,
    RIGHT,
    LEFT
} RelativeDirection;

Vector3 DirectionVector(Direction dir);

Direction DirectionFace(Direction dir, RelativeDirection rel);

typedef struct Point
{
    int x;
    int y;
} Point;

Vector3 PointToVector(Point p);

Point PointFromVector(Vector3 v);

#endif