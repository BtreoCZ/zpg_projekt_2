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



#include <SOIL.h>
#include <vector>
#include "ShaderProgram.h"
#include "Model.h"
#include "bushes.h"
#include "sphere.h"
#include <random>
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "gift.h"
#include "suzi_flat.h"
#include "Controller.h"
#include "Skybox.h"
#include "skycube.h"
#include "DrawableObjectOBJ.h"
#include "ModelOBJ.h"
#include "DynamicRotate.h"
#pragma once
using namespace std;

class Application
{
public:
	GLFWwindow* window;

	vector<ShaderProgram> shaders;
	vector<Model> models;

	vector<Scene*> scenes;
	int currentSceneIndex;

public:

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	void Init();

	void AddScene(Scene *scene);

	void SwitchScene();

	void MoveObject(int direction);

	void RotateObject(int axis);

	void Run();



};
