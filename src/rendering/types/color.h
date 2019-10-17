#ifndef MY_COLOR_H
#define MY_COLOR_H

#include "transformation.h"

namespace rendering::types
{

class Color : public Transformation
{
public:
    static const auto NUMBER_OF_COLORS = 5;

    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

    static Color black();
    static Color white();

    static Color steel_blue();

    // -----------
    // Game Colors
    static Color purple();
    static Color red();
    static Color yellow();
    static Color green();
    static Color orange();
    // Game Colors
    // -----------

    static Color random();

    void apply() override;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

}

#endif