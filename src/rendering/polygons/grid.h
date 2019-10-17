#ifndef MY_GRID_H
#define MY_GRID_H

#include "../types.h"


namespace rendering::polygons
{

using namespace rendering::types;

class Grid: public Drawable
{
public:
    Grid(Vector2 position, int width, int height, int size = 1, Color color = Color::black());
    void draw() override;

private:
    Vector2 position;

    int width;
    int height;
    int size;

    Color color;
};

}

#endif