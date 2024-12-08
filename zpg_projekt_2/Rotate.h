#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Rotate : public TransformationComponent
{
	private:
	glm::vec3 rotation;
	public:
		Rotate();
		Rotate(glm::vec3 rotation);
		glm::mat4 Apply(glm::mat4 model) override;
		glm::mat4 GetMatrix() override;
};

