#pragma once
#ifndef OGLRENDERDATA_H
#define OGLRENDERDATA_H

#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
struct OGLVertex {
    glm::vec3 position;
    glm::vec3 normal;
};

struct OGLV {
    glm::vec3 position;
};
struct OGLM
{
    std::vector<OGLV> vertices;
};
struct OGLMesh {
    std::vector<OGLVertex> vertices;
};

struct OGLRenderData{
    GLFWwindow *rdWindow = nullptr;

    int rdWidth = 0;
    int rdHeight = 0;
    int rdNrAttributes = 0;
    int rdTriangleCount = 0 ;

    bool rdUsePolygonMode = false;

    bool rdIsColorChanged = false;
    int rdVertexColorPosition = 0;
    int rdVertexObjectColorPosition = 0;
    int rdVertexLightColorPosition = 0;

    float rdXLastPos = 0;
    float rdYLastPos = 0;

    float rdYaw = 0.0f;
    float rdPitch = 0.0f;
    float rdFov = 45.0f;

    int cubeCount = 1;

    float rdTickDiff = 0.0f;
    float rdFrameTime = 0.0f;
};

#endif // OGLRENDERDATA_H
