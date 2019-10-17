#include <thread>
#include <mutex>
#include <chrono>
#include <map>
#include <iostream>
#include <memory>
#include <cassert>

#include <GL/freeglut.h>

#include "renderer.h"
#include "types.h"
#include "polygons/block.h"

#include "../logic.h"

using namespace rendering::types;

namespace rendering
{

namespace
{
    // Thread used to run the glut main loop
    auto render_thread = std::thread();

    auto next_frame_time = std::chrono::steady_clock::now();

    auto frame_count = 0;
    auto total_frame_duration = std::chrono::milliseconds();
    auto max_frame_duration = std::chrono::milliseconds();
    auto min_frame_duration = std::chrono::milliseconds();

    std::mutex* drawable_mutex;
    Drawable* drawable;

}

int Renderer::main_window_id = 0;
int Renderer::game_window_id = 0;

void Renderer::init(int* argc, char** argv)
{
    // Does basic glut init stuff
    glutInit(argc, argv);

    // Puts glut in double buffered mode with RGBA colors
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Set standard window size and position
    // glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create our basic window using the title from the header
    main_window_id = glutCreateWindow(WINDOW_TITLE);
    std::cout << "Main window id: " << main_window_id << "\n";

    glutDisplayFunc([]() {
        // std::cout << "[Main display_func] Drawing frame\n";

        glClear (GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
    });

    glutReshapeFunc(reshape_callback);

    game_window_id = glutCreateSubWindow(main_window_id, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "Game window id: " << game_window_id << "\n";

    std::cout << "[Init] Current window: " << glutGetWindow() << "\n";

    // Set our "empty" color
    glClearColor(0.8, 0.8, 0.8, 0.0);

    // Clear the coordinate matrix and put an ortho projection into it
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GAME_WIDTH, 0.0, GAME_HEIGHT);

    // Apply global scale to all drawn objects
    glScaled(GAME_SCALE, GAME_SCALE, GAME_SCALE);

    // Add all the glut callbacks
    glutIdleFunc(idle_callback);
    glutDisplayFunc(display_callback);
    glutCloseFunc(close_callback);

    std::cout << "[Init] Current window: " << glutGetWindow() << "\n";
}

// Starts the glut main loop.
void Renderer::start(Drawable* draw, std::mutex* mutex)
{
    drawable = draw;
    drawable_mutex = mutex;

    std::cout << "[Start] Current window: " << glutGetWindow() << "\n";
    
    glutSetWindow(main_window_id);
    render_thread = std::thread(glutMainLoop);
}

// Stops the glut main loop.
void Renderer::stop()
{
    glutSetWindow(main_window_id);
    glutLeaveMainLoop();
}

// Joins the thread running the glut main loop.
void Renderer::join()
{
    render_thread.join();
}

// void Renderer::add_object(Drawable* object)
// {
//     drawables.insert(object);
// }

// void Renderer::update_drawables(const std::set<Drawable*>& new_drawables)
// {
//     drawables = std::set<Drawable*>(new_drawables);
// }

// Display function called whenever glut goes to render a frame.
void Renderer::display_callback()
{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    assert(glutGetWindow() == game_window_id && "Primary display callback is expected to be used for game window!");

    // Mark start time     
    auto render_start = std::chrono::steady_clock::now();

    // std::cout << "[Sub display] Drawing a frame!\n";

    // Clear the screen fully
    glClear(GL_COLOR_BUFFER_BIT);

    {
        // std::cout << "[Renderer] Waiting to get lock...\n";
        std::lock_guard lock(*drawable_mutex);
        // std::cout << "[Renderer] Got lock!\n";

        drawable->draw();
    }

    // Swap the buffers to put the newly drawn frame on screen
    glutSwapBuffers();

    // Mark end of render
    auto render_end = std::chrono::steady_clock::now();
    // Increment frame count
    frame_count += 1;
    
    // Calculate ideal time for next frame to start
    next_frame_time = render_start + FRAME_DURATION;

    // Find how long the frame took in milliseconds
    auto frame_duration = duration_cast<milliseconds>(render_end - render_start);
    // std::cout << "Frame took: " << frame_duration.count() << "\n";

    // Calculate frame stats using duration
    calculate_stats(frame_duration);
}

// Idle function called when glut is waiting around
void Renderer::idle_callback()
{
    using std::chrono::steady_clock;

    if (steady_clock::now() >= next_frame_time)
    {
        // std::cout << "[Idle] posting redisplay!\n";

        glutSetWindow(main_window_id);
        glutPostRedisplay();

        glutSetWindow(game_window_id);
        glutPostRedisplay();
    }
}

// Callback for when the main window is reshaped.
// Moves the game subwindow into the center of the actual window in use.
void Renderer::reshape_callback(int width, int height)
{
    // Clamp window width to game width
    if (width < WINDOW_WIDTH)
    {
        glutSetWindow(main_window_id);
        glutReshapeWindow(WINDOW_WIDTH, height);
    }

    // Clamp window height to game height
    if (height < WINDOW_HEIGHT)
    {
        glutSetWindow(main_window_id);
        glutReshapeWindow(width, WINDOW_HEIGHT);
    }

    std::cout << "Resizing sub-window!\n";

    // Calculate how far from the left-right edges the subwindow should be
    auto width_minus_game = width - WINDOW_WIDTH;
    if (width_minus_game < 0) width_minus_game = 0;
    auto width_offset = width_minus_game/2;

    // Calculate how far from the top-bottom edges the subwindow should be
    auto height_minus_game = height - WINDOW_HEIGHT;
    if (height_minus_game < 0) height_minus_game = 0;
    auto height_offset = height_minus_game/2;

    std::cout << "Sub-window position: { " << width_offset << ", " << height_offset << " }\n";

    // Apply the calculated offset to the subwindow
    glutSetWindow(game_window_id);
    glutPositionWindow(width_offset, height_offset); 
}

// Callback on window close.
// Prints frame statistics.
void Renderer::close_callback()
{
    using std::cout;
    using std::endl;

    cout << "Total frames drawn: " << frame_count << endl;
    cout << "Average frame time: " << total_frame_duration.count() / frame_count << endl;
    cout << "Maximum frame time: " << max_frame_duration.count() << endl;
    cout << "Minimum frame time: " << min_frame_duration.count() << endl;
}

// Helper function to calculate statistics about frames
void Renderer::calculate_stats(std::chrono::milliseconds frame_duration)
{
    total_frame_duration += frame_duration;

    if (frame_duration > max_frame_duration)
    {
        max_frame_duration = frame_duration;
    }

    if (frame_duration < min_frame_duration)
    {
        min_frame_duration = frame_duration;
    }
}

}