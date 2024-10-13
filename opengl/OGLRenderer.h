#ifndef OGLRENDERER_H
#define OGLRENDERER_H

#include<memory>

#include <iostream>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Timer.h"
#include "OGLRenderData.h"
#include "Shader.h"
#include "Logger.h"
#include "Rectangle.h"
#include "VertexBuffer.h"
#include "UserInterface.h"
#include "UniformBuffer.h"
class OGLRenderer
{
public:
    OGLRenderer(GLFWwindow* win);
    bool init(unsigned int width, unsigned int height);
    void resize(unsigned int width, unsigned int height);
    void handleMousePressEvents(double xPos, double yPos);
    void handleMouseReleasedEvents();
    void draw();
    void cleanUp();

private:
    Timer mFrameTimer{};
    OGLRenderData mRenderData{};
    Shader mShader{};
    VertexBuffer mVertexBuffer{};
    UserInterface mUserInterface{};
    UniformBuffer mUniformBuffer{};

    glm::mat4 mModelMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;

    std::unique_ptr<Rectangle> mTriangle = nullptr;
    double mLastTickTime = 0.0;
    bool mFirstMouse = false;
    std::vector<glm::vec3> rectanglePositions;
    glm::vec3 getRay(float xPos, float yPos);
    glm::vec3 normalise(const glm::vec3 &v);
    bool intersectRayPlane(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &planeNormal, const glm::vec3 &planePoint, float &t);
    bool intersectDisc(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &planeNormal, const glm::vec3 &planePoint, const float &radius);
};

#endif // OGLRENDERER_H
