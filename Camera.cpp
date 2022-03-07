#include "Camera.hpp"
#include <GL/glew.h>

const GLfloat YAW = -90.f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 8.5f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;     

        //TODO - Update the rest of camera parameters
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, cameraUp));
        this->cameraUpDirection = glm::normalize(glm::cross(this->cameraFrontDirection, glm::vec3(1.0f, 0.0f, 0.0f)));

        this->yaw = YAW;
        this->pitch = PITCH;
        this->speed = SPEED;
        this->sensitivity = SENSITIVITY;
        this->zoom = ZOOM;

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 Camera::getCameraTarget()
    {
        return cameraTarget;
    }
    glm::vec3 Camera::getCameraPosition()
    {
        return cameraPosition;
    }
    float Camera::getYaw()
    {
        return this->yaw;
    }
    float Camera::getPitch()
    {
        return this->pitch;
    }

    float Camera::getZoom() {
        return this->zoom;
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        switch (direction) {
            case MOVE_FORWARD:
                cameraPosition += cameraFrontDirection * speed;
                break;
            case MOVE_BACKWARD:
                cameraPosition -= cameraFrontDirection * speed;
                break;
            case MOVE_RIGHT:
                cameraPosition += cameraRightDirection * speed;
                break;
            case MOVE_LEFT:
                cameraPosition -= cameraRightDirection * speed;
                break;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->cameraFrontDirection = glm::normalize(front);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));

    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset)
    {
        xOffset *= this->sensitivity;
        yOffset *= this->sensitivity;

        this->yaw += xOffset;
        this->pitch += yOffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        rotate(pitch, yaw);
    }

    void Camera::ProcessMouseScroll(float yOffset)
    {
        if (this->zoom >= 1.0f && this->zoom <= 45.0f)
        {
            this->zoom -= yOffset;

        }
        if (this->zoom <= 1.0f)
        {
            this->zoom = 1.0f;
        }
        if (this->zoom >= 45.0f)
        {
            this->zoom = 45.0f;
        }
    }

    void Camera::setCameraPosition(glm::vec3 v)
    {
        this->cameraPosition = v;
    }
}