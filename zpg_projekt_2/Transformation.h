
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

public:
    Transformation();

    void AddComponent(TransformationComponent* component);


    glm::mat4 GetMatrix();
};