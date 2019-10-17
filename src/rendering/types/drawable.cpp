#include <iostream>

#include <GL/freeglut.h>

#include "drawable.h"

using namespace rendering::types;

Drawable::~Drawable() {}
void Drawable::draw() {}

void LineTest::draw()
{
    auto width = glutGet(GLUT_WINDOW_WIDTH);
    auto height = glutGet(GLUT_WINDOW_HEIGHT);
    std::cout << "Window width : " << width << ", window height: " << height << "\n";
    
    // Use steel blue as the line color
    glColor3ub(0x46, 0x82, 0xb4);
    glBegin (GL_LINES);
        glVertex2i (0, 0); // Specify line-segment geometry.
        glVertex2i (5, vertex_edge);
    glEnd ( );

    vertex_edge += 1;
}
