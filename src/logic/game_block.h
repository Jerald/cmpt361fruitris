#ifndef MY_GAME_BLOCK_H
#define MY_GAME_BLOCK_H

#include "../rendering.h"

namespace logic
{

using rendering::types::Drawable;

class Block: public Drawable
{
public:
    Block();

    void draw() override;

private:

};


}


#endif