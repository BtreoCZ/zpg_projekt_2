#pragma once
#include "Drawableobject.h"
#include "Observer.h"
class Skybox : public DrawableObject, public Observer
{
private:
	bool followCamera = true;
public:
	Skybox(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal, Camera* camera, std::vector<Light*> lights, Texture* texture);
	Skybox(Model* model, ShaderProgram* shaderProgram, Material* material);
	void SetFollowCamera(bool followCamera);
	bool GetFollowCamera();
	void Update(Subject* subject) override;
	virtual void Draw();
};

