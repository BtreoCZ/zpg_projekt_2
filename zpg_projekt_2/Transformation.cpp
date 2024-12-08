#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation(){}

void Transformation::AddComponent(TransformationComponent* component)
{
    transformations.push_back(component);

    //this->modelMatrix = component->Apply(this->modelMatrix);
}


glm::mat4 Transformation::GetMatrix()
{
    
	glm::mat4 modelMatrix = glm::mat4(1.0f);

    for (TransformationComponent* component : transformations) {

        modelMatrix *= component->GetMatrix();
    }

    return modelMatrix;
}