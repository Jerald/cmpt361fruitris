#include <cassert>
#include <utility>
#include <iostream>

#include "game_grid.h"
#include "tetris.h"

using namespace logic;

GameGrid::GameGrid()
{
    inner_grid.resize(GAME_WIDTH);

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        inner_grid[x].resize(GAME_HEIGHT);

        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            inner_grid[x][y] = {};
        }
    }
}

void GameGrid::draw()
{
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            auto& block = get_block(x, y);

            if (block.has_value())
            {
                block->position = {x, y};
                block->draw();
            }
        }
    }

    auto shape = Tetris::get_current_shape();
    auto blocks = shape.get_blocks();

    for (auto block : blocks)
    {
        block.draw();
    }

    grid_lines.draw();
}

std::optional<polygons::Block>& GameGrid::get_block(int x, int y)
{
    if (x >= GRID_WIDTH || x < 0 || y >= GRID_HEIGHT || y < 0)
    {
        std::cout << "Someone accessed the BLOCK HOLE!\n";
        return block_hole;
    }

    return inner_grid.at(x).at(y);
}

std::optional<polygons::Block>& GameGrid::get_block(types::Vector2 position)
{
    std::cout << "[GameGrid::get_block] Vector2{ " << position.x << ", " << position.y << " }\n";
    return get_block(position.x, position.y);
}

void GameGrid::set_block(types::Vector2 position, const std::optional<polygons::Block>& new_block)
{
    auto& block = get_block(position);
    block = std::optional<polygons::Block>(new_block);
}