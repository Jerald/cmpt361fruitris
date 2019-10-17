#include <cassert>

#include <GL/freeglut.h>

#include "tetris_shape.h"

using namespace rendering::polygons;

TetrisShape::TetrisShape(TetrisShapeType type, Vector2 position, int size)
    : position{position},
    size{size}
{
    switch (type)
    {
        case TetrisShapeType::I:
            add_block(-2, 0);
            add_block(-1, 0);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case TetrisShapeType::S:
            add_block(-1, -1);
            add_block(0, -1);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case TetrisShapeType::L:
            add_block(-1, -1);
            add_block(-1, 0);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case TetrisShapeType::T:
            add_block(-1, 0);
            add_block(0, -1);
            add_block(0, 0);
            add_block(1, 0);
        break;
    }
}

void TetrisShape::draw()
{
    for (int i = -2; i <= 1; i++)
    {
        for (int j = -2; j <= 1; j++)
        {
            if (grid(i, j).has_value())
            {
                grid(i, j)->draw();
            }
        }
    }

    glBegin(GL_LINES);
        Color::steel_blue().apply();

        #ifdef TETRIS_DEBUG_CENTER
            position.draw();
            (position + Vector2{size, size}).draw();
            (position + Vector2{0, size}).draw();
            (position + Vector2{size, 0}).draw();
        #endif

        #ifdef TETRIS_DEBUG_BOUNDS
            (position + Vector2{-2*size, -2*size}).draw();
            (position + Vector2{-2*size, 2*size}).draw();

            (position + Vector2{-2*size, 2*size}).draw();
            (position + Vector2{2*size, 2*size}).draw();

            (position + Vector2{2*size, 2*size}).draw();
            (position + Vector2{2*size, -2*size}).draw();

            (position + Vector2{2*size, -2*size}).draw();
            (position + Vector2{-2*size, -2*size}).draw();
        #endif
    glEnd();
}

int TetrisShape::get_left()
{
    return position.x + left;
}

int TetrisShape::get_right()
{
    return position.x + right + 1;
}

int TetrisShape::get_top()
{
    return position.y + top + 1;
}

int TetrisShape::get_bottom()
{
    return position.y + bottom;
}

std::optional<Block>& TetrisShape::grid(int x, int y)
{
    x += 2;
    y += 2;

    return blocks[x][y];
}

void TetrisShape::add_block(int x, int y, Color color)
{
    if (x > right)
    {
        assert(x >= -2 && x <= 1);
        right = x;
    }

    if (x < left)
    {
        assert(x >= -2 && x <= 1);
        left = x;
    }

    if (y > top)
    {
        assert(y >= -2 && y <= 1); 
        top = y;
    }

    if (y < bottom)
    {
        assert(y >= -2 && y <= 1);
        bottom = y;
    }

    auto block_position = position + Vector2{x*size, y*size};

    // Needs to be a random color eventually
    grid(x, y) = Block(color, block_position, size);
}