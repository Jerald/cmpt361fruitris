#ifndef MY_RENDERER_H
#define MY_RENDERER_H

#include <chrono>
#include <mutex>
#include <thread>
#include <memory>
#include <map>

#include "types.h"

namespace rendering
{

using types::Drawable;

const auto WINDOW_TITLE = "Fruitris - a cmpt361 project";

const auto FPS = 60;
const auto FRAME_DURATION = std::chrono::milliseconds(1000/FPS);

// Size of the coordinate space within the game sub-window
const auto GAME_WIDTH = 10;
const auto GAME_HEIGHT = 20;

// Experimental. Only changes scale matrix
const auto GAME_SCALE = 1.0;

// Size of the sub-window the game plays in.
// Also the minimum size of the main window.
const auto WINDOW_WIDTH = 300;
const auto WINDOW_HEIGHT = 600;


class Renderer
{
public:
    Renderer() = delete;

    static void init(int* argc, char** argv);

    static void start(
        Drawable* drawable,
        std::mutex* drawable_mutex);
    static void stop();

    static void join();

    static int main_window_id;
    static int game_window_id;

    // static void add_object(Drawable* object);

    // static void update_drawables(const std::set<Drawable*>& new_drawables);

private:
    // Display function called whenever glut goes to render a frame.
    static void display_callback();
    // Idle function called when glut is waiting around
    static void idle_callback();
    // Callback for when the main window is reshaped.
    // Moves the game subwindow into the center of the actual window in use.
    static void reshape_callback(int width, int height);
    // Callback on window close.
    // Prints frame statistics.
    static void close_callback();

    
    // Helper function to calculate statistics about frames
    static void calculate_stats(std::chrono::milliseconds frame_duration);
};

}

#endif