#include <map>
#include <memory>
#include <chrono>

#include <GL/freeglut.h>

#include <iostream>

#include "../rendering.h"
#include "tetris.h"

#include "game_shape.h"

using rendering::Drawable;

namespace logic
{

namespace
{
    auto game_thread = std::thread();
    auto next_tick_time = std::chrono::steady_clock::now();

    auto drop_timout = TICK_RATE;
    
    auto* game_grid = new GameGrid();
    auto* game_grid_mutex = new std::mutex();

    auto current_shape = Shape({3, 10}, ShapeType::L);

    bool up_pressed = false;
    bool down_pressed = false;
    bool left_pressed = false;
    bool right_pressed = false;

    bool should_stop = false;
}

void Tetris::init(int* argc, char** argv)
{
    Renderer::init(argc, argv);

    std::cout << "[Tetris] main window id: " << Renderer::main_window_id << "\n";

    glutSetWindow(Renderer::main_window_id);
    glutSpecialFunc(special_key_callback);

    glutSetWindow(Renderer::game_window_id);
    glutSpecialFunc(special_key_callback);
}

void Tetris::start()
{
    std::cout << "[Tetris] Grid pointer: " << game_grid << "\n";

    Renderer::start(game_grid, game_grid_mutex);
    game_thread = std::thread(main_loop);
}

void Tetris::stop()
{
    should_stop = true;
}

void Tetris::join()
{
    game_thread.join();
}

void Tetris::main_loop()
{
    using std::chrono::steady_clock;

    while (true)
    {
        if (should_stop == true)
        {
            cleanup();
            return;
        }

        if (steady_clock::now() >= next_tick_time)
        {
            tick();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}

void Tetris::tick()
{
    using std::chrono::steady_clock;

    auto tick_start = steady_clock::now();
    
    {
        input_handler();

        drop_timout -= 1;
        if (drop_timout == 0)
        {
            drop_timout = TICK_RATE;
            checked_shape_drop();
        }
        
    }

    [[maybe_unused]] auto tick_end = steady_clock::now();
    next_tick_time = tick_start + TICK_DURATION;
}

void Tetris::checked_shape_drop()
{
    std::cout << "Doing checked shape drop!\n";
    current_shape.move_down();
    std::cout << "Block has dropped...\n";

    if (current_shape.get_bottom() <= 0)
    {
        current_shape.freeze();
        spawn_shape();
    }
    else if (current_shape.check_overlap())
    {
        std::cout << "Found overlap on drop!\n";
        current_shape.move_up();
        current_shape.freeze();
        spawn_shape();
    }
}

GameGrid* Tetris::get_game_grid()
{
    return game_grid;
}

std::mutex* Tetris::get_game_grid_mutex()
{
    return game_grid_mutex;
}

Shape& Tetris::get_current_shape()
{
    return current_shape;
}

void Tetris::spawn_shape()
{
    current_shape = Shape::random({4, 18});
}


void Tetris::input_handler()
{
    if (up_pressed)
    {
        std::cout << "Rotating shape!\n";
        current_shape.rotate();
    }

    if (left_pressed)
    {
        // if (current_shape.get_left() > 0) current_shape.move_left();
        current_shape.move_left();
    }

    if (right_pressed)
    {
        // if (current_shape.get_right() < GAME_WIDTH-1) current_shape.move_right();
        current_shape.move_right();
    }

    if (down_pressed)
    {
        checked_shape_drop();
    }

    up_pressed = false;
    down_pressed = false;
    left_pressed = false;
    right_pressed = false;
}

void Tetris::special_key_callback(int key, [[maybe_unused]] int x, [[maybe_unused]] int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            up_pressed = true;
        break;

        case GLUT_KEY_DOWN:
            down_pressed = true;
        break;

        case GLUT_KEY_LEFT:
            left_pressed = true;
        break;

        case GLUT_KEY_RIGHT:
            right_pressed = true;
        break;
    }
}

void Tetris::cleanup()
{

}

}
