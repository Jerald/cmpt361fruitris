#include <iostream>
#include <cassert>

#include "game_shape.h"
#include "tetris.h"

#include "../rendering.h"

using namespace rendering;


namespace logic
{

Shape::Shape(types::Vector2 position, ShapeType type)
    : position{position}
{
    switch (type)
    {
        case ShapeType::I:
            add_block(-2, 0);
            add_block(-1, 0);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case ShapeType::S:
            add_block(-1, -1);
            add_block(0, -1);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case ShapeType::L:
            add_block(-1, -1);
            add_block(-1, 0);
            add_block(0, 0);
            add_block(1, 0);
        break;

        case ShapeType::T:
            add_block(0, -1);
            add_block(-1, 0);
            add_block(0, 0);
            add_block(1, 0);
        break;
    }

    update_bounds();
}

Shape Shape::random(types::Vector2 position)
{
    static_assert(NUMBER_OF_SHAPES == 4, "Someone changed NUMBER_OF_SHAPES without changing Shape::random()!");

    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

    switch (std::rand() % NUMBER_OF_SHAPES)
    {
        case 0: return Shape(position, ShapeType::I);
        case 1: return Shape(position, ShapeType::S);
        case 2: return Shape(position, ShapeType::L);
        case 3: return Shape(position, ShapeType::T);
    }
    
    assert(false && "This should literally never be possible. Shape::random()'s switch wasn't exhaustive...");
}

// Clockwise rotation matrix by 90 degrees:
// [  0, -1 ]
// [  1,  0 ]
// Net effect on [x, y] is becoming [y, -x]
void Shape::rotate()
{
    for (auto& block : blocks)
    {
        auto pos = block.position;

        // Net effect of 90 degree clockwise rotation matrix
        auto new_pos = types::Vector2{ -pos.y, pos.x };

        auto abs_pos = position + pos;
        auto abs_new_pos = position + new_pos;

        if ((pos.x == new_pos.x) && (pos.y == new_pos.y))
        {
            std::cout << "Rotation was isomorphic!\n";
        }
        else
        {
            block.position = new_pos;
        }

        std::cout << "[Rotation] Original pos: { " << pos.x << ", " << pos.y << " }, new pos: { " << new_pos.x << ", " << new_pos.y << " }\n";
    }

    update_bounds();

    if (check_overlap())
    {
        rotate_clockwise();
    }
}

void Shape::rotate_clockwise()
{
    for (auto& block : blocks)
    {
        auto pos = block.position;

        // Net effect of 90 degree clockwise rotation matrix
        auto new_pos = types::Vector2{ pos.y, -pos.x };

        auto abs_pos = position + pos;
        auto abs_new_pos = position + new_pos;

        if ((pos.x == new_pos.x) && (pos.y == new_pos.y))
        {
            std::cout << "Rotation was isomorphic!\n";
        }
        else
        {
            block.position = new_pos;
        }

        std::cout << "[Rotation] Original pos: { " << pos.x << ", " << pos.y << " }, new pos: { " << new_pos.x << ", " << new_pos.y << " }\n";
    }

    update_bounds();
}

void Shape::move_up()
{
    position = position + types::Vector2{0, 1};

    if (check_overlap()) move_down();
}


void Shape::move_down()
{
    position = position - types::Vector2{0, 1};

    // if (check_overlap()) move_up();
}

void Shape::move_left()
{
    position = position - types::Vector2{1, 0};
    if (check_overlap()) move_right();
}

void Shape::move_right()
{
    position = position + types::Vector2{1, 0};
    if (check_overlap()) move_left();
}

int Shape::get_top()
{
    std::cout << "[Shape::get_top] Top: " << position.y + top << "\n";
    return position.y + top;
}

int Shape::get_bottom()
{
    std::cout << "[Shape::get_bottom] Bottom: " << position.y + bottom << "\n";
    return position.y + bottom;
}

int Shape::get_left()
{
    std::cout << "[Shape::get_left] Left: " << position.x + left << "\n";
    return position.x + left;
}

int Shape::get_right()
{
    std::cout << "[Shape::get_right] Right: " << position.x + right << "\n";
    return position.x + right;
}

void Shape::freeze()
{
    auto grid = Tetris::get_game_grid();
    auto out_blocks = get_blocks();

    for (auto block : out_blocks)
    {
        grid->set_block(block.position, block);
    }
}

bool Shape::check_overlap()
{
    for (auto block : get_blocks())
    {
        std::cout << "[check_overlap] Block position: { " << block.position.x << ", " << block.position.y << " }\n";
        if (Tetris::get_game_grid()->get_block(block.position).has_value())
        {
            std::cout << "Found an overlap!\n";
            return true;
        }
    }

    std::cout << "Found no overlap :(\n";
    return false;
}

std::vector<polygons::Block> Shape::get_blocks()
{
    auto out_vector = std::vector(blocks);

    for (auto& block : out_vector)
    {
        block.position = block.position + position;
    }

    return out_vector;
}

std::vector<polygons::Block>& Shape::get_blocks_ref()
{
    return blocks;
}

void Shape::add_block(int x, int y)
{
    auto new_block = polygons::Block(types::Color::random(), {x, y});
    blocks.push_back(new_block);
}

void Shape::update_bounds()
{
    top = 0;
    bottom = GAME_HEIGHT;
    left = GAME_WIDTH;
    right = 0;

    for (auto block : blocks)
    {
        auto pos = block.position;

        std::cout << "Pos: { " << pos.x << ", " << pos.y << " }\n";

        if (pos.x > right) right = pos.x;
        if (pos.x < left) left = pos.x;

        if (pos.y > top) top = pos.y;
        if (pos.y < bottom) bottom = pos.y;
    }

    std::cout << "Bounds after update: top: " << top << ", bottom: " << bottom << ", left: " << left << ", right: " << right << "\n";
}

}