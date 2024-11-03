#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation(){}

void Transformation::AddComponent(TransformationComponent* component)
{
    transformations.push_back(component);

    this->modelMatrix = component->Apply(this->modelMatrix);
}


glm::mat4 Transformation::GetMatrix()
{
    return this->modelMatrix;
}