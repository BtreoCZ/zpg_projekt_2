#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
    : position(0.0f, 5.0f, 5.0f), target(0.0f, 0.0f, 0.0f), projectionMatrix(glm::mat4(1.0f))
{
    movementSpeed = 2.5f;
	UpdateCameraVectors();
    
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed)
    : position(position), target(target), movementSpeed(movementSpeed), up(up), projectionMatrix(glm::mat4(1.0f))
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projectionMatrix;
}

void Camera::SetPosition(glm::vec3& pos)
{
    position = pos;
    Notify(); 
}

void Camera::SetTarget(glm::vec3& tgt)
{
    target = tgt;
    Notify(); 
}

void Camera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    Notify();
}

void Camera::Attach(Observer* shaderProgram)
{
    observers.push_back(shaderProgram);
}

void Camera::Detach(Observer* shaderProgram)
{
    observers.erase(std::remove(observers.begin(), observers.end(), shaderProgram), observers.end());
}

void Camera::ProcessKeyboardInput(int direction, float deltaTime)
{
    UpdateCameraVectors();
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += target * velocity;
    if (direction == BACKWARD)
        position -= target * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;

    Notify();
}

void Camera::Rotate(float deltaX, float deltaY)
{
    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;


    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    target = glm::normalize(direction);

    Notify();
}

void Camera::UpdateCameraVectors()
{
    right = glm::normalize(glm::cross(target, up));
}



void Camera::Notify()
{
    for (auto& observer : this->observers)
    {
        if (observer)  
        {
            observer->Update();
        }
    }
}
