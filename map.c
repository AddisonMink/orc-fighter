#include <map.h>
#include <raylib.h>

void DrawMap3D()
{
    for (int x = 0; x < MAP_SIZE; x++)
    {
        Vector3 topPos = PointToVector((Point){x, 0});
        DrawCube(topPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
        DrawCubeWires(topPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);

        Vector3 botPos = PointToVector((Point){x, MAP_SIZE - 1});
        DrawCube(botPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
        DrawCubeWires(botPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);
    }

    for (int y = 1; y < MAP_SIZE - 1; y++)
    {
        Vector3 leftPos = PointToVector((Point){0, y});
        DrawCube(leftPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
        DrawCubeWires(leftPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);

        Vector3 rightPos = PointToVector((Point){MAP_SIZE - 1, y});
        DrawCube(rightPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
        DrawCubeWires(rightPos, TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);
    }
}

bool MapInBounds(Point p)
{
    return p.x > 0 && p.x < MAP_SIZE - 1 && p.y > 0 && p.y < MAP_SIZE - 1;
}