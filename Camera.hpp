#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <string>

namespace gps {
    
    enum MOVE_DIRECTION {MOVE_FORWARD, MOVE_BACKWARD, MOVE_RIGHT, MOVE_LEFT};
    
    class Camera
    {
    public:
        //Camera constructor
        Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
        //return the view matrix, using the glm::lookAt() function
        glm::mat4 getViewMatrix();

        glm::vec3 getCameraTarget();
        glm::vec3 getCameraPosition();
        glm::vec3 getCameraUp();
        float getYaw();
        float getPitch();
        void setCameraPosition(glm::vec3 v);
        //update the camera internal parameters following a camera move event
        void move(MOVE_DIRECTION direction, float speed);
        //update the camera internal parameters following a camera rotate event
        //yaw - camera rotation around the y axis
        //pitch - camera rotation around the x axis
        void rotate(float pitch, float yaw);

        void ProcessMouseMovement(float xOffset, float yOffset);
        void ProcessMouseScroll(float yOffset);
        float getZoom();
        
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 cameraFrontDirection;
        glm::vec3 cameraRightDirection;
        glm::vec3 cameraUpDirection;

        float yaw;
        float pitch;

        float speed;
        float sensitivity;
        float zoom;
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            front.y = sin(glm::radians(this->pitch));
            front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            this->cameraFrontDirection = glm::normalize(front);
        }
    };
    
}

#endif /* Camera_hpp */
