
#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"
using namespace std;
class Transformation
{
private:
    vector<TransformationComponent*> transformations;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

public:
    Transformation();

    void AddComponent(TransformationComponent* component);


    glm::mat4 GetMatrix();
};