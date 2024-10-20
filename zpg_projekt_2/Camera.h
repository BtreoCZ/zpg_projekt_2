#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed);
    Camera();


    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target);
    void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);

    void ProcessKeyboardInput(int direction, float deltaTime);


    void Attach(ShaderProgram* shaderProgram);

    void Notify() const;

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 front;   
    glm::vec3 up;      
    glm::vec3 right;   
    glm::vec3 worldUp; 

    float movementSpeed;
    glm::mat4 projectionMatrix;

    std::vector<ShaderProgram*> observers;


    void UpdateCameraVectors();
};
