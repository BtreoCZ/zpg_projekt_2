#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Subject.h"

using namespace std;
class Light : public Subject,public Observer
{
	private:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 objectColor;
	float intensity;
	float ambientStrenght;

	vector<Observer*> observers;

	public:
		Light(glm::vec3 position, glm::vec3 color, glm::vec3 objectColor, float intensity, float ambientStrenght);
		glm::vec3 GetPosition();
		glm::vec3 GetColor();
		glm::vec3 GetObjectColor();
		float GetIntensity();
		float GetAmbientStrenght();
		void SetPosition(glm::vec3 position);
		void SetColor(glm::vec3 color);
		void SetObjectColor(glm::vec3 objectColor);
		void SetIntensity(float intensity);
		void SetAmbientStrenght(float ambientStrenght);
		void Attach(Observer* observer) override;
		void Detach(Observer* observer) override;
		void Notify() override;
		void Update(Subject *subject) override;
};

