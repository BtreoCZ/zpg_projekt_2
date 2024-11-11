#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdio.h>
#include "Camera.h"
#include "Observer.h"
#include "ShaderLoader.h"
#include "Light.h"

class Camera;


class ShaderProgram : Observer
{
private:
	GLuint shader_id;

	GLenum mode;
	GLint first;
	GLsizei count;
	ShaderLoader shaderLoader;
	Camera* camera;
	vector<Light*> lights;


public:
	glm::mat4 Matrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;


	ShaderProgram(GLenum mode, GLint first, GLsizei count,Camera *camera, vector<Light*> lights);

	void setLights(vector<Light*> lights);


	void AddShaders(const char* vertex_shader, const char* fragment_shader);

	void UpdateViewAndProjection(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	void SetMatrix(glm::mat4 Matrix);

	void CheckProgramLinking(GLuint program);

	void SetMat4Uniform(const char* uniformName, glm::mat4 matrix);

	void SetMat3Uniform(const char* uniformName, glm::mat3 matrix);

	void SetVec3Uniform(const char* uniformName, glm::vec3 vector);

	void SetVec4Uniform(const char* uniformName, glm::vec4 vector);

	void SetFloatUniform(const char* uniformName, float value);

	void UseProgram();

	void DetachProgram();

	void Update(Subject* subject) override;

	void Draw();
};
