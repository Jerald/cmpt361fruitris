#ifndef MY_TETRIS_H
#define MY_TETRIS_H

#include <chrono>
#include <memory>

#include "game_grid.h"
#include "game_shape.h"

namespace logic
{

const auto TICK_RATE = 20;
const auto TICK_DURATION = std::chrono::milliseconds(1000/TICK_RATE);

class Tetris
{
public:
    Tetris() = delete;

    static void init(int* argc, char** argv);
    static void start();
    static void stop();
    static void join();

    static void main_loop();
    static void tick();

    static logic::GameGrid* get_game_grid();
    static std::mutex* get_game_grid_mutex();

    static Shape& get_current_shape();

private:
    static void checked_shape_drop();
    static void spawn_shape();

    static void input_handler();

    static void special_key_callback(int key, int x, int y);

    static void cleanup();

};

}

#endif