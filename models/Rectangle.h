#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "OGLRenderData.h"
class Rectangle
{
public:
    void init();
    OGLMesh getData();
private:
    OGLMesh mVertexData;
};

#endif // RECTANGLE_H
