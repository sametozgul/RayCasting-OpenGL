#include "Camera.h"


Camera::Camera()
{

}

Camera::Camera(glm::vec3 position)
{
    Position = position;
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Front = glm::vec3(0.0f, 0.0f, 1.0f);
    mViewMatrix = glm::mat4(1.0f);
    mViewMatrix = glm::lookAt(Position, Position + Front, Up);
    // setWorldAngle();
}

void Camera::setXRotation(int angle)
{
    // if(angle < 0 || angle > 90)
    //     return;
    if (angle != m_xRot) {
        m_xRot = angle;
        setWorldAngle();
    }
}

void Camera::setYRotation(int angle)
{
    // if(angle > 0 || angle < -90)
    //     return;
    if (angle != m_yRot) {
        m_yRot = angle;
        setWorldAngle();
    }
}

glm::mat4 Camera::getViewMatrix()
{
    return mViewMatrix;
}
void Camera::cameraZoomingEvent(float yoffset)
{
    if(yoffset>0){
        mZoomingVector += glm::vec3(0.1f, 0.1f, 0.1f);

    }else{
        mZoomingVector -= glm::vec3(0.1f, 0.1f, 0.1f);
    }
    if( mZoomingVector.x <= 0.5f )
        mZoomingVector = glm::vec3(0.5f);
    setWorldAngle();
}

int Camera::xRot() const
{
    return m_xRot;
}

int Camera::yRot() const
{
    return m_yRot;
}

void Camera::setWorldAngle()
{
    mViewMatrix = glm::mat4(1.0f);
    mViewMatrix = glm::translate(mViewMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
    mViewMatrix = glm::scale(mViewMatrix, mZoomingVector);
    mViewMatrix = glm::rotate(mViewMatrix, glm::radians((float)m_xRot), glm::vec3(1.0f, 0.0f, 0.0f));
    mViewMatrix = glm::rotate(mViewMatrix, glm::radians((float)m_yRot), glm::vec3(0.0f, 1.0f, 0.0f));
    mViewMatrix = glm::rotate(mViewMatrix, glm::radians((float)m_zRot), glm::vec3(0.0f, 0.0f, 1.0f));
}
