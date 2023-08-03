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

Vector3 DirectionTurnToward(Direction d, RelativeDirection dir, float fraction);

typedef struct Point
{
    int x;
    int y;
} Point;

bool PointEqual(Point p1, Point p2);

Point PointAdd(Point p1, Point p2);

Point PointSubtract(Point p1, Point p2);

Direction PointToward(Point p1, Point p2);

Point PointAddDirection(Point p, Direction dir);

float PointDistance(Point p1, Point p2);

Vector3 PointToVector(Point p);

Point PointFromVector(Vector3 v);

#endif