#ifndef MY_BLOCK_H
#define MY_BLOCK_H

#include "../types.h"


namespace rendering::polygons
{

using namespace rendering::types;

class Block : public Drawable
{
public:
    Block(Color color = Color::random(), Vector2 position = {0, 0}, int size = 1);
    void draw() override;

    int get_left();
    int get_right();
    int get_top();
    int get_bottom();

    Color color;
    Vector2 position;

private:

    int size;
};

}

#endif