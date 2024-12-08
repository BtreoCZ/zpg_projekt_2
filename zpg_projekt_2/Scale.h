#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Scale : public TransformationComponent
{
	private:
	glm::vec3 scale;
	public:
		Scale(glm::vec3 scale);
		glm::mat4 Apply(glm::mat4 model);
		glm::mat4 GetMatrix();
};

