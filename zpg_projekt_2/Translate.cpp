#include "Translate.h"

Translate::Translate(glm::vec3 translation)
{
	this->translation = translation;
}

glm::mat4 Translate::Apply(glm::mat4 model)
{
	return glm::translate(model, translation);
}

glm::mat4 Translate::GetMatrix()
{
	return glm::translate(glm::mat4(1.0f), translation);
}
