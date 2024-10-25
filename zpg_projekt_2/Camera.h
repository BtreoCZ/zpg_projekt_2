#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "Subject.h"
#include "Observer.h"

class ShaderProgram;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera : Subject
{
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed);
    Camera();


    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void SetPosition(glm::vec3& position);
    void SetTarget(glm::vec3& target);
    void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);

    void ProcessKeyboardInput(int direction, float deltaTime);

    void Rotate(float deltaX, float deltaY);

    void Attach(Observer* shaderProgram) override;

    void Detach(Observer* shaderProgram) override;

    void Notify() override;

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;      
    glm::vec3 right;   

    float yaw;
    float pitch;

    float movementSpeed;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    std::vector<Observer*> observers;


    void UpdateCameraVectors();
};
