/*----------------------------------------------------------------------
    FILE        : Camera.h
    AUTHOR      : Samet ÖZGÜL, Tubitak
    LAST UPDATE : 08.19.2024

    Header file of Camera can help Opengl View proccess.

    All Rights Free
-----------------------------------------------------------------------*/
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    Camera();
    Camera(glm::vec3 position);
    void setXRotation(int angle);
    void setYRotation(int angle);
    glm::mat4 getViewMatrix();

    void cameraZoomingEvent(float yoffset);
    float getZoom(){return mZoom;}
    int xRot() const;

    int yRot() const;

private:
    int m_xRot = 1;
    int m_yRot = 1;
    int m_zRot = 1;

    float mZoom = 45.0f;
    float mZoominngFactor = 0.01;
    glm::vec3 mZoomingVector{1.0f,1.0f,1.0f};
    void setWorldAngle();

    glm::mat4 mViewMatrix;
};

#endif // CAMERA_H
