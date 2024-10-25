#include "Application.h"
#include "plain.h"

vector<DrawableObject> objects;
vector<DrawableObject> objects2;

float deltaTime = 0.0f;  
float lastFrame = 0.0f;  

void Application::Init()
{
	Camera* camera = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);
	Camera* camera2 = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);

	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(this->window, this);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Sets the key callback
	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);


	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);

	const char* vertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"void main() {\n"
		"    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
		"    ourColor = aColor;\n"
		"}\n";

	const char* fragmentShader =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"    fragColor = vec4(ourColor, 1.0);\n"
		"}\n";



	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";



	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	const char* fragment_shader_quad =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0, 1, 0, 1.0);"
		"}";

	float quad[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};



	camera->SetProjection(60.0f,ratio, 0.1f, 100.0f);
	camera2->SetProjection(60.0f, ratio, 0.1f, 100.0f);

	srand(time(NULL));
	;


	for (int i = 0; i < 20; i++) {
		DrawableObject treeObject(tree, sizeof(tree), GL_TRIANGLES, vertexShader, fragmentShader, true,camera);
		treeObject.SetScale(glm::vec3(rand() % 100 / 1000.0 + 0.05f));
		treeObject.SetPosition(glm::vec3(rand() % 20 - 8, 0.0f, rand()%50));

		float randomAngleY = rand() % 45;
		float randomAngleX = rand() % 45;

		//treeObject.SetRotation(glm::vec3(randomAngleX, randomAngleY, 0));

		DrawableObject bushObject(bushes, sizeof(bushes), GL_TRIANGLES, vertexShader, fragmentShader, true, camera);
		bushObject.SetScale(glm::vec3(rand() % 100 / 500.0 + 0.05f));
		bushObject.SetPosition(glm::vec3(rand() % 8 - 5, rand() % 8 - 5, 0.0f));

		objects.push_back(treeObject);
		objects.push_back(bushObject);
	}

	DrawableObject plainObject(plain, sizeof(plain), GL_TRIANGLES, vertexShader, fragmentShader, true, camera);
	plainObject.SetScale(glm::vec3(10.0f));
	plainObject.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	objects.push_back(plainObject);

	Scene *scene1= new Scene(objects, camera);
	AddScene(scene1);

	DrawableObject kulicka(sphere, sizeof(sphere), GL_TRIANGLES, vertexShader, fragmentShader, true, camera2);
	kulicka.SetScale(glm::vec3(0.5f));

	objects2.push_back(kulicka);

	DrawableObject obdelnik(quad, sizeof(quad), GL_QUADS, vertexShader, fragment_shader_quad, false, camera2);
	obdelnik.SetScale(glm::vec3(0.5f));
	obdelnik.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));

	objects2.push_back(obdelnik);

	Scene *scene2 = new Scene(objects2, camera2);

	AddScene(scene2);

	currentSceneIndex = 0;

}

void Application::AddScene(Scene *scene)
{
	scenes.push_back(scene);
}

void Application::SwitchScene()
{
	currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
}



void Application::MoveObject(int direction)
{
	printf("MoveObject %d\n", direction);

	for (auto& object : scenes[currentSceneIndex]->objects)
	{
		if (direction == 0) {
			object.SetPosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
		else if (direction == 1) {
			object.SetPosition(glm::vec3(0.1f, 0.0f, 0.0f));
		}
		else if (direction == 2) {
			object.SetPosition(glm::vec3(0.0f, 0.1f, 0.0f));
		}
		else if (direction == 3) {
			object.SetPosition(glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}
}

void Application::RotateObject(int axis)
{

	for (auto& object : scenes[currentSceneIndex]->objects)
	{
		if (axis == 0) {
			object.SetRotation(glm::vec3(0.0f, 0.0f, 10.0f));
		}
		else if (axis == 1) {
			object.SetRotation(glm::vec3(0.0f, 10.0f, 0.0f));
		}
	}
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);



	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		scenes[currentSceneIndex]->Render();


		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	for (auto& model : models) {
		model.DeleteModel();
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
}



void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	const float maxDeltaTime = 0.01f;

	if (deltaTime > maxDeltaTime) {
		deltaTime = maxDeltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboardInput(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboardInput(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboardInput(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboardInput(RIGHT, deltaTime);
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
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

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		app->SwitchScene();
	}

}