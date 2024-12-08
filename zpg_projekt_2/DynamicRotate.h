#pragma once
#include "Rotate.h"
class DynamicRotate : public Rotate
{
private:
	float speed;
	glm::vec3 rotation;
	glm::vec3 rotationPos;
public:
	DynamicRotate();
	DynamicRotate(glm::vec3 rotation, float speed);
	glm::mat4 GetMatrix() override;
};

