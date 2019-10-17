#include <GL/freeglut.h>

#include "block.h"

using namespace rendering::polygons;

Block::Block(Color color, Vector2 position, int size)
    : color{color},
    position{position},
    size{size}
{}

void Block::draw()
{
    glBegin(GL_QUADS);
        color.apply();

        position.draw();
        (position + Vector2{size, 0}).draw();
        (position + Vector2(size, size)).draw();
        (position + Vector2(0, size)).draw();
    glEnd();
}

int Block::get_left()
{
    return position.x;
}

int Block::get_right()
{
    return position.x + size;
}

int Block::get_top()
{
    return position.y + size;
}

int Block::get_bottom()
{
    return position.y;
}