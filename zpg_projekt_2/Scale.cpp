#include "Scale.h"

Scale::Scale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::mat4 Scale::Apply(glm::mat4 model)
{
	return glm::scale(model, scale);
}

glm::mat4 Scale::GetMatrix()
{
	return glm::scale(glm::mat4(1.0f), scale);
}
