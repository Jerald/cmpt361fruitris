#ifndef MY_DRAWABLE_H
#define MY_DRAWABLE_H



namespace rendering::types
{

class Drawable
{
public:
    virtual ~Drawable();
    virtual void draw();
};

class LineTest : public Drawable
{
public:
    void draw() override;

private:
    int vertex_edge = 0;
};

}

#endif