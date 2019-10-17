#ifndef MY_TRANSFORMATION_H
#define MY_TRANSFORMATION_H

namespace rendering::types
{

// A transformation that can be applied to rendering between glBeing() and glEnd()
class Transformation
{
public:
    virtual ~Transformation();

    virtual void apply();
    
private:
};

}

#endif