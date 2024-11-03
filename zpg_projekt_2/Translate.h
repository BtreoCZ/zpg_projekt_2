#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Translate : public TransformationComponent
{

	private:
	glm::vec3 translation;
	public:
		Translate(glm::vec3 translation);
		glm::mat4 Apply(glm::mat4 model) override;
};

