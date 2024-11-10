#include "Controller.h"

void Controller::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_LEFT) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(0);
		}
		else if (key == GLFW_KEY_RIGHT) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(1);
		}
		else if (key == GLFW_KEY_UP) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(2);
		}
		else if (key == GLFW_KEY_DOWN) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(3);
		}
		else if (key == GLFW_KEY_R) {
			((Application*)glfwGetWindowUserPointer(window))->RotateObject(0);
		}
		else if (key == GLFW_KEY_T) {
			((Application*)glfwGetWindowUserPointer(window))->RotateObject(1);
		}
		else if (key == GLFW_KEY_SPACE) {
			((Application*)glfwGetWindowUserPointer(window))->SwitchScene();
		}
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
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	Camera* camera = app->scenes[app->currentSceneIndex]->GetCamera();

	static double lastX = 400, lastY = 300;

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

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		app->SwitchScene();
	}

}
