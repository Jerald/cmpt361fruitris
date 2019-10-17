#ifndef MY_GAME_SHAPE_H
#define MY_GAME_SHAPE_H

#include <vector>

#include "game_grid.h"
#include "../rendering.h"

namespace logic
{

enum ShapeType { I, S, L, T };

class Shape
{
public:
    static const auto NUMBER_OF_SHAPES = 4;

    Shape(types::Vector2 position, ShapeType type);

    static Shape random(types::Vector2 position);

    void rotate();
    void rotate_clockwise();

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    int get_top();
    int get_bottom();
    int get_left();
    int get_right();

    void freeze();

    bool check_overlap();

    std::vector<polygons::Block> get_blocks();

    std::vector<polygons::Block>& get_blocks_ref();

private:
    void add_block(int x, int y);
    void update_bounds();

    int top = 0;
    int bottom = GAME_HEIGHT;
    int left = GAME_WIDTH;
    int right = 0;

    rendering::types::Vector2 position;
    std::vector<polygons::Block> blocks;
};

}


#endif