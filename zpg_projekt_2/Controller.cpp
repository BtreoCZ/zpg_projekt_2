#include "Controller.h"


int cx, cy;
bool firstMouse = true;
bool isCursorEnabled = false;
void Controller::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		app->SwitchScene();
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		Skybox* skybox =  app->scenes[app->currentSceneIndex]->GetSkybox();

		if (skybox != nullptr)
			skybox->SetFollowCamera(!skybox->GetFollowCamera());
		if (skybox->GetFollowCamera() == false)
			skybox->SetPosition(camera->GetPosition());
		else
			skybox->transformation = Transformation();
			
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	float currentFrame = glfwGetTime();
	app->deltaTime = currentFrame - app->lastFrame;
	app->lastFrame = currentFrame;

	const float maxDeltaTime = 0.01f;

	if (app->deltaTime > maxDeltaTime) {
		app->deltaTime = maxDeltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboardInput(FORWARD, app->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboardInput(BACKWARD, app->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboardInput(LEFT, app->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboardInput(RIGHT, app->deltaTime);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();

	camera->SetProjection(60.0f, width / (float)height, 0.1f, 100.0f);

	glViewport(0, 0, width, height);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	cx = x;
	cy = y;

	if (isCursorEnabled == false)
		return;
	static double lastX = 400, lastY = 300;

	if (firstMouse) {
		lastX = x;
		lastY = y;

		firstMouse = false;
	}


	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();

	

	double offsetX = x - lastX;
	double offsetY = lastY - y;

	lastX = x;
	lastY = y;

	float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	camera->Rotate(offsetX, offsetY);
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		cursor_callback(window, cx, cy);
		isCursorEnabled = true;
		firstMouse = true;
		
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		isCursorEnabled = false;
	}
	if (button == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		app->SwitchScene();
	}

	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	GLint x = (GLint)cx;
	GLint y = (GLint)cy;

	//int newy = camera->getResolution().y – y;
	int newy = height - y;
	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

	glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjectionMatrix();
	glm::vec4 viewPort = glm::vec4(0, 0, width, height);
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	app->scenes[app->currentSceneIndex]->CreateTree(pos);


	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);


}
