#include <cstdlib>
#include <cassert>
#include <chrono>

#include <GL/freeglut.h>

#include "color.h"

using namespace rendering::types;

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    : r{red},
    g{green},
    b{blue},
    a{alpha}
{}

Color Color::black()        { return {0x00, 0x00, 0x00}; }
Color Color::white()        { return {0xff, 0xff, 0xff}; }
Color Color::steel_blue()   { return {0x46, 0x82, 0xb4}; }

// -----------
// Game Colors
Color Color::purple()       { return {0x9B, 0x59, 0xB6}; }
Color Color::red()          { return {0xC0, 0x39, 0x2B}; }
Color Color::yellow()       { return {0xF1, 0xC4, 0x0F}; }
Color Color::green()        { return {0x2E, 0xCC, 0x71}; }
Color Color::orange()       { return {0xF3, 0x9C, 0x12}; }
// Game Colors
// -----------

Color Color::random()
{
    static_assert(NUMBER_OF_COLORS == 5, "Someone changed NUMBER_OF_COLORS without changing Color::random()!");

    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

    switch (std::rand() % NUMBER_OF_COLORS)
    {
        case 0: return purple();
        case 1: return red();
        case 2: return yellow();
        case 3: return green();
        case 4: return orange();
    }
    
    assert(false && "This should literally never be possible. Color::random()'s switch wasn't exhaustive...");
}

void Color::apply()
{
    glColor4ub(r, g, b, a);
}