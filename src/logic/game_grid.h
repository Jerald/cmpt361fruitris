#ifndef MY_GAME_GRID_H
#define MY_GAME_GRID_H

#include <optional>
#include <vector>

#include "../rendering.h"


namespace logic
{

using namespace rendering;

const auto GRID_WIDTH = 10;
const auto GRID_HEIGHT = 20;

class GameGrid : public types::Drawable
{
public:
    GameGrid();

    void draw() override;

    std::optional<polygons::Block>& get_block(int x, int y);
    std::optional<polygons::Block>& get_block(types::Vector2 position);

    void set_block(types::Vector2 position, const std::optional<polygons::Block>& new_block);

    // polygons::Block take_block(int x, int y);
    // polygons::Block take_block(types::Vector2 position);

private:
    std::vector<std::vector<std::optional<polygons::Block>>> inner_grid;
    polygons::Grid grid_lines = polygons::Grid({0, 0}, GRID_WIDTH, GRID_HEIGHT);


    // Yes, I primarily made this for the pun.
    // It's the "wildcard" or "empty" block if something is out of range
    std::optional<polygons::Block> block_hole = polygons::Block();
};

}

#endif