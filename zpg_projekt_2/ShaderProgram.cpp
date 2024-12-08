#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count,Camera *camera, vector<Light*> lights)
{
	this->shader_id = 0;

	this->mode = mode;
	this->first = first;
	this->count = count;
	
	this->shaderLoader = ShaderLoader();
	this->camera = camera;

	camera->Attach(this);

	this->lights = lights;

	for (auto light : lights) {
		light->Attach(this);
		light->Notify();
	}

	camera->Notify();

	setLights(lights);
}

void ShaderProgram::setLights(std::vector<Light*> lights) {
	for (size_t i = 0; i < lights.size(); ++i) {
		std::string lightIndex = "lights[" + std::to_string(i) + "].";


		this->SetVec3Uniform((lightIndex + "position").c_str(), lights[i]->GetPosition());


		this->SetVec3Uniform((lightIndex + "color").c_str(), lights[i]->GetColor());


		this->SetFloatUniform((lightIndex + "intensity").c_str(), lights[i]->GetIntensity());
	}
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

	this->shaderLoader = ShaderLoader(vertex_shader,fragment_shader,&this->shader_id);

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	//glCompileShader(vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	//glCompileShader(fragmentShader);

	//this->shader_id = glCreateProgram();

	//glAttachShader(this->shader_id, vertexShader);
	//glAttachShader(this->shader_id, fragmentShader);
	//glLinkProgram(this->shader_id);

	//CheckProgramLinking(this->shader_id);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
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
void ShaderProgram::SetMat4Uniform(const char* uniformName, glm::mat4 matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetMat3Uniform(const char* uniformName, glm::mat3 matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniformMatrix3fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetVec3Uniform(const char* uniformName, glm::vec3 vector)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform3fv(idModelTransform, 1, glm::value_ptr(vector));
}
void ShaderProgram::SetVec4Uniform(const char* uniformName, glm::vec4 vector)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform4fv(idModelTransform, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetFloatUniform(const char* uniformName, float value)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform1f(idModelTransform, value);
}
void ShaderProgram::SetIntUniform(const char* uniformName, int value)
{
	GLint idUniform = glGetUniformLocation(this->shader_id, uniformName);

	if (idUniform == -1) {
		return;
	}

	glUniform1i(idUniform, value);
}

void ShaderProgram::SetBoolUniform(const char* uniformName, bool value)
{
	GLint idUniform = glGetUniformLocation(this->shader_id, uniformName);

	if (idUniform == -1) {
		return;
	}

	glUniform1i(idUniform, value);
}

void ShaderProgram::UseProgram()
{

	glUseProgram(this->shader_id);

}

void ShaderProgram::DetachProgram()
{
	glUseProgram(0);
}

void ShaderProgram::Update(Subject* subject)
{
	this->UseProgram();
	
	if (typeid(*subject)==typeid(Camera))
	{
		this->SetMat4Uniform("viewMatrix", this->camera->GetViewMatrix());
		this->SetMat4Uniform("projectionMatrix", this->camera->GetProjectionMatrix());
		SetVec3Uniform("viewPosition", camera->GetPosition());
	}
	else if (typeid(*subject) == typeid(Light))
	{
		Light* light = (Light*)subject;
		string lightIndex = "lights[" + std::to_string(light->GetIndex()) + "].";


		this->SetVec3Uniform((lightIndex + "position").c_str(), light->GetPosition());


		this->SetVec3Uniform((lightIndex + "color").c_str(), light->GetColor());

		this->SetVec3Uniform((lightIndex + "direction").c_str(), light->GetDirection());

		this->SetIntUniform((lightIndex + "type").c_str(), light->GetType());


		this->SetFloatUniform((lightIndex + "intensity").c_str(), light->GetIntensity());

	}

	this->DetachProgram();
}

vector<Light*> ShaderProgram::getLights()
{
	return this->lights;
}

void ShaderProgram::Draw()
{
	glDrawArrays(this->mode, this->first, this->count);
}

void ShaderProgram::DrawOBJ() 
{
	glDrawElements(GL_TRIANGLES, this->count, GL_UNSIGNED_INT, NULL);
}
