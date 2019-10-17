#ifndef MY_TETRIS_SHAPE_H
#define MY_TETRIS_SHAPE_H

#include <optional>

#include "../types.h"
#include "block.h"


namespace rendering::polygons
{

using namespace rendering::types;

#define TETRIS_DEBUG_BOUNDS
#define TETRIS_DEBUG_CENTER

enum TetrisShapeType { I, S, L, T };

class TetrisShape: public Drawable
{
public:
    TetrisShape(TetrisShapeType type, Vector2 position, int size = 1);
    void draw() override;

    int get_left();
    int get_right();
    int get_top();
    int get_bottom();

private:
    std::optional<Block>& grid(int x, int y);
    void add_block(int x, int y, Color color = Color::random());

    std::optional<Block> blocks[4][4];   

    Vector2 position;
    int size;

    int left = 2;
    int right = -2;
    int top = -2;
    int bottom = 2;
};

}


#endif