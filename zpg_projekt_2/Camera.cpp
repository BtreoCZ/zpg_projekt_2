#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
    : position(0.0f, 5.0f, 5.0f), target(0.0f, 0.0f, 0.0f), projectionMatrix(glm::mat4(1.0f))
{
    movementSpeed = 2.5f;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	UpdateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed)
    : position(position), target(target), movementSpeed(movementSpeed), worldUp(up), projectionMatrix(glm::mat4(1.0f))
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return viewMatrix; //glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::SetPosition(const glm::vec3& pos)
{
    position = pos;
    Notify(); 
}

void Camera::SetTarget(const glm::vec3& tgt)
{
    target = tgt;
    Notify(); 
}

void Camera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    Notify();
}

void Camera::Attach(ShaderProgram* shaderProgram)
{
    observers.push_back(shaderProgram);
}

void Camera::ProcessKeyboardInput(int direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += target * velocity;
    if (direction == BACKWARD)
        position -= target * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;

    UpdateViewMatrix();
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
    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);
}


void Camera::Notify() const
{
    for (ShaderProgram* observer : observers)
    {
        observer->UpdateViewAndProjection(GetViewMatrix(), GetProjectionMatrix());
    }
}
