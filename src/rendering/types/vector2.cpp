#include <GL/freeglut.h>

#include "vector2.h"

using namespace rendering::types;

Vector2::Vector2(int x, int y)
    : x{x},
    y{y}
{}

// Uses the vector2 as a vertex position
void Vector2::draw()
{
    glVertex2i(x, y);
}

Vector2 Vector2::operator+(const Vector2 rhs)
{
    return { x + rhs.x, y + rhs.y };
}

Vector2 Vector2::operator-(const Vector2 rhs)
{
    return { x - rhs.x, y - rhs.y };
}

bool Vector2::operator<(const Vector2 rhs) const
{
    return (y < rhs.y );
}