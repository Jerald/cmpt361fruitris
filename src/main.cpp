#include <iostream>
#include <chrono>

#include <map>

#include <memory>

#include <GL/glut.h>

#include "rendering.h"
#include "logic.h"

using rendering::Renderer;
using rendering::Drawable;
using rendering::types::Color;
using rendering::polygons::Block;

using logic::Tetris;

int main(int argc, char** argv)
{
    std::cout << "Starting...\n";
    
    // Renderer::init(&argc, argv);
    // std::cout << "Initialized renderer!\n";

    Tetris::init(&argc, argv);
    std::cout << "Initialized tetris!\n";
    Tetris::start();
    std::cout << "Started tetris!\n";

    std::cout << "Joining tetris...\n";
    Tetris::join();

    // auto drawables = std::make_shared<std::multimap<int, Drawable*>>();
    // std::shared_ptr<logic::Grid> drawable = std::make_shared<logic::Grid>();
    // auto drawables_mutex = new std::mutex();

    // drawable->get_block(1, 1) = Block();
    // drawable->get_block(2, 2) = Block();

    // drawable->get_block(5, 5) = Block();

    // drawable->get_block(9, 5) = Block();



    // {
    //     std::lock_guard lock(*drawables_mutex);

    //     drawables->insert({5,
    //         new Block(Color::purple(), {5, 10}, 1) });

    //     drawables->insert({5,
    //         new TetrisShape(TetrisShapeType::I, {3, 3}, 1) });

    //     drawables->insert({100,
    //         new Grid({0, 0}, GAME_WIDTH, GAME_HEIGHT) });
    // }

    // Renderer::add_object(new Block(Color::purple(), {5, 10}, 1));

    // Renderer::add_object(
    //     new Block(
    //         Color::purple(),
    //         Vector2{100, 200}));

    // Renderer::add_object(new Block(Color::red(), {150, 200}));
    // Renderer::add_object(new Block(Color::yellow(), {200, 200}));
    // Renderer::add_object(new Block(Color::green(), {250, 200}));
    // Renderer::add_object(new Block(Color::orange(), {300, 200}));

    // Renderer::add_object(
    //     new TetrisShape(TetrisShapeType::I, {5, 5}, 1));

    // Renderer::add_object(
    //     new TetrisShape(TetrisShapeType::S, {200, 300}));

    // Renderer::add_object(
    //     new TetrisShape(TetrisShapeType::L, {250, 300}));

    // Renderer::add_object(
    //     new TetrisShape(TetrisShapeType::T, {300, 300}));
    
    // Renderer::start(drawables, drawables_mutex);

    // auto drawable_arg = static_cast<std::shared_ptr<Drawable>>(drawable);

    // Renderer::start(drawable_arg, drawables_mutex);
    // std::cout << "Started render thread!\n";



    // Renderer::join();

    return 0;
}




