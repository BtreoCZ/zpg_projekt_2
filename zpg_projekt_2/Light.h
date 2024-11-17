#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Subject.h"
#include "Camera.h"

using namespace std;
class Light : public Subject,public Observer
{
	private:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 objectColor;
	float intensity;
	float ambientStrenght;
	glm::vec3 direction;
	float angle;
	int type;
	int index;

	vector<Observer*> observers;

	public:
		Light(glm::vec3 position, glm::vec3 color, glm::vec3 objectColor, float intensity, float ambientStrenght,glm::vec3 direction,int type);
		glm::vec3 GetPosition();
		glm::vec3 GetColor();
		glm::vec3 GetObjectColor();
		glm::vec3 GetDirection();
		int GetType();
		float GetIntensity();
		float GetAmbientStrenght();
		int GetIndex();
		void SetIndex(int index);
		void SetPosition(glm::vec3 position);
		void SetColor(glm::vec3 color);
		void SetObjectColor(glm::vec3 objectColor);
		void SetDirection(glm::vec3 direction);
		void SetType(int type);
		void SetIntensity(float intensity);
		void SetAmbientStrenght(float ambientStrenght);
		void Attach(Observer* observer) override;
		void Detach(Observer* observer) override;
		void Notify() override;
		void Update(Subject *subject) override;
};

