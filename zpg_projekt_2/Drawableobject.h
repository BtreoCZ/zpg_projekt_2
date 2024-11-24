#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
#include "ModelTexture.h"

class Transformation;

class DrawableObject
{
public:
    Model model;
    ModelTexture modelTexture;
    Transformation transformation;

    ShaderProgram *shaderProgram;

    Material* material;

	Texture* texture;

    bool hasNormal;
	bool hasTexture = false;

    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal,Camera *camera,vector<Light*> lights);
    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal, Camera* camera, vector<Light*> lights,Texture* texture);
    DrawableObject(Model* model, ShaderProgram* shaderProgram,Material *material);
    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotationDegrees);
    void SetScale(glm::vec3 scale);
    void EnableDynamicRotation(float speed, const glm::vec3& axis);
    void UpdateRotation(float deltaTime);
	void setMaterial(Material* material);
	void setTexture(Texture* texture);

    void Draw();

private:
    bool isDynamicRotationEnabled = false;
    float rotationSpeed = 0.0f;       
    glm::vec3 rotationAxis;           
    float currentRotationAngle = 0.0f; 
};