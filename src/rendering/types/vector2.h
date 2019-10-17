#ifndef MY_VECTOR2_H
#define MY_VECTOR2_H

#include "drawable.h"

namespace rendering::types
{

class Vector2 : public Drawable
{
public:
    Vector2(int x, int y);

    // Uses the vector2 as a vertex position
    void draw() override;
    
    Vector2 operator+(const Vector2 rhs);
    Vector2 operator-(const Vector2 rhs);

    bool operator<(const Vector2 rhs) const;
    bool operator>(const Vector2 rhs) const;

    int x;
    int y;
};

}

#endif