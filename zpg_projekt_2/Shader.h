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

class Shader
{
private:
	GLuint shader_id;

	GLenum mode;
	GLint first;
	GLsizei count;

public:
	Shader(GLenum mode, GLint first, GLsizei count);

	void AddShaders(const char* vertex_shader, const char* fragment_shader);

	void CheckProgramLinking(GLuint program);

	void UseProgram(glm::mat4& M);

	void Draw();
};