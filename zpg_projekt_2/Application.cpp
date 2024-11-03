#include "Application.h"
#include "plain.h"



float deltaTime = 0.0f;  
float lastFrame = 0.0f;  

void Application::Init()
{
	vector<DrawableObject*> objects_forest;
	vector<DrawableObject*> objects_spheres;
	vector<DrawableObject*> objects_triangle;
	vector<DrawableObject*> objects_shaders;

	Camera* camera_forest = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);
	Camera* camera_spheres = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f);
	Camera* camera_base = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);
	Camera* camera_shaders = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);

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

	const char* vertexShader_light =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"

		"out vec4 ex_worldPosition\n"
		"out vec3 ex_worldNormal"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"void main() {\n"
		"    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
		"    ourColor = aColor;\n"
		"    ex_worldPosition = modelMatrix * vec4(aPos,1.0f);\n"
		"    ex_worldNormal = normalMatrix * in_Normal;\n"
		"}\n";

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

	const char* fragmentShader_light =
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


	//Nastavení kamer
	camera_forest->SetProjection(60.0f,ratio, 0.1f, 100.0f);
	camera_spheres->SetProjection(60.0f, ratio, 0.1f, 100.0f);
	camera_base->SetProjection(60.0f, ratio, 0.1f, 100.0f);
	camera_shaders->SetProjection(60.0f, ratio, 0.1f, 100.0f);

	camera_spheres->Rotate(-90.0f, 0.0f);
	camera_shaders->Rotate(-90.0f, 0.0f);

	const float triangle[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.5f, 1.0f, 0.0f
	};
	Light* light = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.0f, 0.2f);

	Light* light_spheres = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.0f, 0.2f);


	srand(time(NULL));
	;


	//Vytvoøení sceny pro trojuhelnik
	DrawableObject* triangle_object = new DrawableObject(triangle, sizeof(triangle), GL_TRIANGLES, "vertex.txt", "fragment.txt", false, camera_base, light);

	objects_triangle.push_back(triangle_object);
	light->Notify();
	Scene* scene_triangle = new Scene(objects_triangle, camera_base);

	AddScene(scene_triangle);
	//Vytvoøeni sceny pro stromy a keøe
	Model* tree_model = new Model();
	tree_model->GenerateModel(tree, sizeof(tree));

	Model* bush_model = new Model();
	bush_model->GenerateModel(bushes, sizeof(bushes));

	ShaderProgram* shader_tree= new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6, camera_forest, light);
	shader_tree->AddShaders("vertex.txt", "phong.txt");
	ShaderProgram* shader_bush = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6, camera_forest, light);
	shader_bush->AddShaders("vertex.txt", "phong.txt");
	for (int i = 0; i < 50; i++) {
		DrawableObject* treeObject = new DrawableObject(tree_model,shader_tree);
		treeObject->SetScale(glm::vec3(rand() % 100 / 1000.0 + 0.05f));
		treeObject->SetPosition(glm::vec3(rand() % 20 - 8, 0.0f, rand()%50));

		float randomAngleY = rand() % 45;
		float randomAngleX = rand() % 45;

		//treeObject.SetRotation(glm::vec3(randomAngleX, randomAngleY, 0));

		DrawableObject* bushObject = new DrawableObject(bush_model,shader_bush);
		bushObject->SetScale(glm::vec3(rand() % 100 / 500.0 + 0.05f));
		bushObject->SetPosition(glm::vec3(rand() % 20 - 8, 0.0f, rand() % 50));

		objects_forest.push_back(treeObject);
		objects_forest.push_back(bushObject);
	}

	DrawableObject* plainObject= new DrawableObject(plain, sizeof(plain), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_forest, light);
	plainObject->SetScale(glm::vec3(10.0f));
	plainObject->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	objects_forest.push_back(plainObject);

	light->Notify();

	Scene *scene_forest= new Scene(objects_forest, camera_forest);
	AddScene(scene_forest);

	//vytvoøení scény pro koule
	DrawableObject* sphereObject = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_spheres, light_spheres);
	sphereObject->SetScale(glm::vec3(0.5f));
	sphereObject->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));


	objects_spheres.push_back(sphereObject);

	DrawableObject* sphereObject2 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_spheres, light_spheres);
	sphereObject2->SetScale(glm::vec3(0.5f));
	sphereObject2->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	objects_spheres.push_back(sphereObject2);

	DrawableObject* sphereObject3 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_spheres, light_spheres);
	sphereObject3->SetScale(glm::vec3(0.5f));
	sphereObject3->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	objects_spheres.push_back(sphereObject3);

	DrawableObject* sphereObject4 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_spheres, light_spheres);
	sphereObject4->SetScale(glm::vec3(0.5f));
	sphereObject4->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));

	objects_spheres.push_back(sphereObject4);


	light_spheres->Notify();

	Scene *scene_spheres = new Scene(objects_spheres, camera_spheres);

	AddScene(scene_spheres);

	DrawableObject* giftObject = new DrawableObject(gift, sizeof(gift), GL_TRIANGLES, "vertex.txt", "fragment.txt", true, camera_shaders, light);
	giftObject->SetScale(glm::vec3(0.5f));
	giftObject->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));

	objects_shaders.push_back(giftObject);

	DrawableObject* suziObject = new DrawableObject(suziFlat, sizeof(suziFlat), GL_TRIANGLES, "vertex.txt", "phong.txt", true, camera_shaders, light);
	suziObject->SetScale(glm::vec3(0.5f));
	suziObject->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	objects_shaders.push_back(suziObject);

	DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), GL_TRIANGLES, "vertex.txt", "blinn.txt", true, camera_shaders, light);
	treeObject->SetScale(glm::vec3(0.5f));
	treeObject->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	objects_shaders.push_back(treeObject);

	DrawableObject* sphereObjectShader = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "FragmentConstant.txt", true, camera_shaders, light);
	sphereObjectShader->SetScale(glm::vec3(0.5f));
	sphereObjectShader->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));

	objects_shaders.push_back(sphereObjectShader);

	light->Notify();

	Scene *scene_shaders = new Scene(objects_shaders, camera_shaders);
	AddScene(scene_shaders);



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
			object->SetPosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
		else if (direction == 1) {
			object->SetPosition(glm::vec3(0.1f, 0.0f, 0.0f));
		}
		else if (direction == 2) {
			object->SetPosition(glm::vec3(0.0f, 0.1f, 0.0f));
		}
		else if (direction == 3) {
			object->SetPosition(glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}
}

void Application::RotateObject(int axis)
{

	for (auto& object : scenes[currentSceneIndex]->objects)
	{
		if (axis == 0) {
			object->SetRotation(glm::vec3(0.0f, 0.0f, 10.0f));
		}
		else if (axis == 1) {
			object->SetRotation(glm::vec3(0.0f, 10.0f, 0.0f));
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