#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 objectColor, float intensity, float ambientStrenght)
{
	this->position = position;
	this->color = color;
	this->objectColor = objectColor;
	this->intensity = intensity;
	this->ambientStrenght = ambientStrenght;
}

glm::vec3 Light::GetPosition()
{
	return this->position;
}

glm::vec3 Light::GetColor()
{
	return this->color;
}

glm::vec3 Light::GetObjectColor()
{
	return this->objectColor;
}

float Light::GetIntensity()
{
	return this->intensity;
}

float Light::GetAmbientStrenght()
{
	return this->ambientStrenght;
}

void Light::SetPosition(glm::vec3 position)
{
	this->position = position;
	this->Notify();
}

void Light::SetColor(glm::vec3 color)
{
	this->color = color;
	this->Notify();
}

void Light::SetObjectColor(glm::vec3 objectColor)
{
	this->objectColor = objectColor;
	this->Notify();
}

void Light::SetIntensity(float intensity)
{
	this->intensity = intensity;
	this->Notify();
}

void Light::SetAmbientStrenght(float ambientStrenght)
{
	this->ambientStrenght = ambientStrenght;
	this->Notify();
}

void Light::Attach(Observer* observer)
{
	this->observers.push_back(observer);
	this->Notify();
}

void Light::Detach(Observer* observer)
{
	this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
	this->Notify();
}

void Light::Notify()
{
	for (Observer* observer : this->observers)
	{
		observer->Update(this);
	}
}

void Light::Update(Subject* subject)
{
}

