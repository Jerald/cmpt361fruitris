#include <GL/freeglut.h>

#include "grid.h"

using namespace rendering::polygons;

Grid::Grid(Vector2 position, int width, int height, int size, Color color)
    : position{position},
    width{width},
    height{height},
    size{size},
    color{color}
{}

void Grid::draw()
{
    glBegin(GL_LINES);
        color.apply();

        for (int x = 0; x < width; x++)
        {
            (position + Vector2{x, 0}).draw();
            (position + Vector2{x, size*height}).draw();
        }

        for (int y = 0; y < height; y++)
        {
            (position + Vector2{0, y}).draw();
            (position + Vector2{size*width, y}).draw();
        }
    glEnd();
}