#include "Rectangle.h"

void Rectangle::init()
{
    mVertexData.vertices.resize(6);
    mVertexData.vertices[0].position = glm::vec3(-0.5f, -0.5f,  0.0f);
    mVertexData.vertices[1].position = glm::vec3( 0.5f,  0.5f,  0.0f);
    mVertexData.vertices[2].position = glm::vec3(-0.5f,  0.5f,  0.0f);

    mVertexData.vertices[3].position = glm::vec3( 0.5f,  0.5f,  0.0f);
    mVertexData.vertices[4].position = glm::vec3( 0.5f,  -0.5f,  0.0f);
    mVertexData.vertices[5].position = glm::vec3( -0.5f,  -0.5f,  0.0f);

}

OGLMesh Rectangle::getData()
{
    if(mVertexData.vertices.size() == 0){
        init();
    }
    return mVertexData;
}
