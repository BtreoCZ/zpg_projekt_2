#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count,Camera *camera)
{
	this->shader_id = 0;

	this->mode = mode;
	this->first = first;
	this->count = count;

	this->camera = camera;

	camera->Attach(this);

}

void ShaderProgram::UpdateViewAndProjection(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	this->viewMatrix = viewMatrix;
	this->projectionMatrix = projectionMatrix;

	GLuint viewMatrixLocation = glGetUniformLocation(shader_id, "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(shader_id, "projectionMatrix");

	glUseProgram(shader_id);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}


void ShaderProgram::AddShaders(const char* vertex_shader, const char* fragment_shader)
{

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	this->shader_id = glCreateProgram();

	glAttachShader(this->shader_id, vertexShader);
	glAttachShader(this->shader_id, fragmentShader);
	glLinkProgram(this->shader_id);

	CheckProgramLinking(this->shader_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::SetMatrix(glm::mat4 Matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, "modelMatrix");

	if (idModelTransform == -1) {
		printf("Error: Cannot find uniform 'modelMatrix' in shader!\n");
	}

	glUseProgram(this->shader_id);

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &Matrix[0][0]);
}


void ShaderProgram::CheckProgramLinking(GLuint program)
{

	GLint status;

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Program linking failure: %s\n", strInfoLog);

		delete[] strInfoLog;

		exit(EXIT_FAILURE);
	}

}

void ShaderProgram::UseProgram()
{

	glUseProgram(this->shader_id);

}

void ShaderProgram::Update()
{
	this->UseProgram();
	this->UpdateViewAndProjection(this->camera->GetViewMatrix(), this->camera->GetProjectionMatrix());
}

void ShaderProgram::Draw()
{
	glDrawArrays(this->mode, this->first, this->count);
}
