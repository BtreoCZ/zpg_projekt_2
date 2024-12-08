#include "DynamicRotate.h"

DynamicRotate::DynamicRotate() : Rotate()
{
	this->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	this->speed = 1.0f;
	this->rotationPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

DynamicRotate::DynamicRotate(glm::vec3 rotation, float speed) : Rotate(rotation)
{
	this->rotation = rotation;
	this->speed = speed;
	this->rotationPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::mat4 DynamicRotate::GetMatrix()
{
    glm::mat4 result = glm::mat4(1.0f);

	this->rotationPos.x += this->speed * this->rotation.x;
	this->rotationPos.y += this->speed* this->rotation.y;
	this->rotationPos.z += this->speed* this->rotation.z;

	if (this->rotationPos.x > 360.0f) this->rotationPos.x -= 360.0f;
	if (this->rotationPos.y > 360.0f) this->rotationPos.y -= 360.0f;
	if (this->rotationPos.z > 360.0f) this->rotationPos.z -= 360.0f;

    result = glm::rotate(result, glm::radians(this->rotationPos.x), glm::vec3(1.0f, 0.0f, 0.0f));
    result = glm::rotate(result, glm::radians(this->rotationPos.y), glm::vec3(0.0f, 1.0f, 0.0f));
    result = glm::rotate(result, glm::radians(this->rotationPos.z), glm::vec3(0.0f, 0.0f, 1.0f));

   
    return result;

}
