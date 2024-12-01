#include "Application.h"
#include "plain.h"

float deltaTime2 = 0;
float lastFrame2 = 0;
int Texture::textureCount = 0;

void Application::Init()
{
	vector<DrawableObject*> objects_forest;
	vector<DrawableObject*> objects_spheres;
	vector<DrawableObject*> objects_triangle;
	vector<DrawableObject*> objects_shaders;

	Camera* camera_forest = new Camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);
	Camera* camera_spheres = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f);
	Camera* camera_base = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);
	Camera* camera_shaders = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f);

	

	glfwSetErrorCallback(Controller::error_callback);
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

	//// Sets the key callback
	glfwSetKeyCallback(this->window, Controller::key_callback);

	glfwSetCursorPosCallback(this->window, Controller::cursor_callback);

	glfwSetMouseButtonCallback(this->window, Controller::button_callback);


	glfwSetWindowFocusCallback(this->window, Controller::window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, Controller::window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, Controller::window_size_callback);


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
	vector<string> filePaths = {
	"posx.jpg",
	"negx.jpg",
	"posy.jpg",
	"tnegy.jpg",
	"posz.jpg",
	"negz.jpg"
	};

	//Nastavení kamer
	camera_forest->SetProjection(60.0f,ratio, 0.1f, 100.0f);
	camera_spheres->SetProjection(60.0f, ratio, 0.1f, 100.0f);
	camera_base->SetProjection(60.0f, ratio, 0.1f, 100.0f);
	camera_shaders->SetProjection(60.0f, ratio, 0.1f, 100.0f);

	camera_spheres->Rotate(-90.0f, 0.0f);
	camera_shaders->Rotate(-90.0f, 0.0f);
	camera_base->Rotate(-90.0f, 0.0f);

	const float triangle[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.5f, 1.0f, 0.0f
	};

	const float plain_texture[] = {
		//vrchol, normála, uv souřadnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};
	Light* light = new Light(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 0.5f, 0.3f,camera_forest->GetTarget(),2);
	light->SetIndex(0);

	Light* light_forest = new Light(glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 0.5f, 0.3f,glm::vec3(0.0),0);
	light_forest->SetIndex(1);

	//Light* light_forest2 = new Light(glm::vec3(0.0f, 1.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 0.5f, 0.3f, glm::vec3(0.0), 0);
	//light_forest2->SetIndex(2);

	Light* light_spheres = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.0f, 0.2f, glm::vec3(0.0), 1);

	vector<Light*> lights;
	lights.push_back(light);
	camera_forest->Attach(light);
	lights.push_back(light_forest);
	//lights.push_back(light_forest2);
	vector<Light*> lights_spheres;
	lights_spheres.push_back(light_spheres);

	srand(time(NULL));
	Texture* plainTexture = new Texture;
	plainTexture->LoadTexture("grass.png");

	Texture* woodenTexture = new Texture;
	woodenTexture->LoadTexture("test.png");
	
	Material* treeMaterial = new Material(0.4f, 0.6f, 0.1f);

	////Vytvoøení sceny pro trojuhelnik
	DrawableObject* triangle_object = new DrawableObject(plain_texture, sizeof(plain_texture), GL_TRIANGLES, "vertex.txt", "fragmentTexture.txt", true, camera_base, lights_spheres, plainTexture);
	triangle_object->setMaterial(treeMaterial);

	objects_triangle.push_back(triangle_object);


	 
	Texture* skyboxTexture = new Texture;
	skyboxTexture->LoadCubeMap(filePaths);

	Model* skycubeModel = new Model();
	skycubeModel->GenerateModelWithoutNormals(skycube, sizeof(skycube));

	ShaderProgram* skyboxShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float) / 3, camera_base, lights_spheres);
	skyboxShader->AddShaders("skybox_vertex.txt", "skybox_fragment.txt");

	Skybox* skybox = new Skybox(skycubeModel, skyboxShader, treeMaterial);
	skybox->setTexture(skyboxTexture);
	skybox->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	skybox->SetScale(glm::vec3(2.0f));
	//camera_base->Attach(skybox);


	light->Notify();


	Scene* scene_triangle = new Scene(objects_triangle, camera_base, skybox);
	AddScene(scene_triangle);
	//Vytvoøeni sceny pro stromy a keøe

	Model* tree_model = new Model();
	tree_model->GenerateModel(tree, sizeof(tree));

	Model* bush_model = new Model();
	bush_model->GenerateModel(bushes, sizeof(bushes));

	ShaderProgram* shader_tree= new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6, camera_forest, lights);
	shader_tree->AddShaders("vertex.txt", "phong_lights.txt");
	ShaderProgram* shader_bush = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6, camera_forest, lights);
	shader_bush->AddShaders("vertex.txt", "phong_lights.txt");

	

	for (int i = 0; i < 50; i++) {
		DrawableObject* treeObject = new DrawableObject(tree_model,shader_tree, treeMaterial);
		if(i%2){
		treeObject->EnableDynamicRotation(20.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		treeObject->SetScale(glm::vec3(rand() % 100 / 1000.0 + 0.05f));
		treeObject->SetPosition(glm::vec3(rand() % 20 - 8, 0.0f, rand()%50));

		float randomAngleY = rand() % 45;
		float randomAngleX = rand() % 45;

		//treeObject.SetRotation(glm::vec3(randomAngleX, randomAngleY, 0));

		DrawableObject* bushObject = new DrawableObject(bush_model,shader_bush, treeMaterial);
		bushObject->SetScale(glm::vec3(rand() % 100 / 500.0 + 0.05f));
		bushObject->SetPosition(glm::vec3(rand() % 20 - 8, 0.0f, rand() % 50));

		objects_forest.push_back(treeObject);
		objects_forest.push_back(bushObject);
	}

	
	DrawableObject* plainObject= new DrawableObject(plain_texture, sizeof(plain_texture), GL_TRIANGLES, "vertex.txt", "fragmentTexture.txt", true, camera_forest, lights,plainTexture);

	plainObject->SetScale(glm::vec3(10.0f));
	plainObject->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	plainObject->setMaterial(treeMaterial);


	objects_forest.push_back(plainObject);



	////new Skybox(skycubeModel, skyboxShader, treeMaterial);
	////Skybox* skybox = new Skybox(skycube, sizeof(skycube), GL_TRIANGLES, "vertex.txt", "fragmentTexture.txt", false, camera_forest, lights, skyboxTexture);
	//DrawableObject* skybox = new DrawableObject(skycubeModel, skyboxShader, treeMaterial);
	////skybox->setTexture(skyboxTexture);
	//skybox->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//skybox->SetScale(glm::vec3(5.0f));
	//skybox->setMaterial(treeMaterial);

	//objects_forest.push_back(skybox);

	light->Notify();

	Scene *scene_forest= new Scene(objects_forest, camera_forest);
	AddScene(scene_forest);

	Material* metal = new Material(0.1, 0.3, 1.0);
	//vytvoøení scény pro koule
	DrawableObject* sphereObject = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong_lights.txt", true, camera_spheres, lights_spheres);
	sphereObject->SetScale(glm::vec3(0.5f));
	sphereObject->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
	sphereObject->setMaterial(metal);


	objects_spheres.push_back(sphereObject);

	Material* glass = new Material(0.1, 0.05, 0.9);
	DrawableObject* sphereObject2 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong_lights.txt", true, camera_spheres, lights_spheres);
	sphereObject2->SetScale(glm::vec3(0.5f));
	sphereObject2->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	sphereObject2->setMaterial(glass);

	objects_spheres.push_back(sphereObject2);

	Material* wood = new Material(0.4, 0.6, 0.1);
	DrawableObject* sphereObject3 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong_lights.txt", true, camera_spheres, lights_spheres);
	sphereObject3->SetScale(glm::vec3(0.5f));
	sphereObject3->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	sphereObject3->setMaterial(wood);

	objects_spheres.push_back(sphereObject3);

	Material* plastic = new Material(0.2, 0.5, 0.3);
	DrawableObject* sphereObject4 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "phong_lights.txt", true, camera_spheres, lights_spheres);
	sphereObject4->SetScale(glm::vec3(0.5f));
	sphereObject4->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));
	sphereObject4->setMaterial(plastic);

	objects_spheres.push_back(sphereObject4);






	light_spheres->Notify();

	Scene *scene_spheres = new Scene(objects_spheres, camera_spheres);

	AddScene(scene_spheres);

	//DrawableObject* giftObject = new DrawableObject(gift, sizeof(gift), GL_TRIANGLES, "vertex.txt", "fragment.txt", true, camera_shaders, lights);
	//giftObject->SetScale(glm::vec3(0.5f));
	//giftObject->SetPosition(glm::vec3(-3.0f, 0.0f, 0.0f));

	//objects_shaders.push_back(giftObject);

	//DrawableObject* suziObject = new DrawableObject(suziFlat, sizeof(suziFlat), GL_TRIANGLES, "vertex.txt", "phong_lights.txt", true, camera_shaders, lights);
	//suziObject->SetScale(glm::vec3(0.5f));
	//suziObject->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	//objects_shaders.push_back(suziObject);

	//DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), GL_TRIANGLES, "vertex.txt", "blinn.txt", true, camera_shaders, lights);
	//treeObject->SetScale(glm::vec3(0.5f));
	//treeObject->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	//objects_shaders.push_back(treeObject);

	//DrawableObject* sphereObjectShader = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "vertex.txt", "FragmentConstant.txt", true, camera_shaders, lights);
	//sphereObjectShader->SetScale(glm::vec3(0.5f));
	//sphereObjectShader->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));

	//objects_shaders.push_back(sphereObjectShader);

	//light->Notify();

	//Scene *scene_shaders = new Scene(objects_shaders, camera_shaders);
	//AddScene(scene_shaders);



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

	float currentFrame = glfwGetTime();
	deltaTime2 = currentFrame - lastFrame2;
	lastFrame2 = currentFrame;

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& object : scenes[currentSceneIndex]->objects) {
			object->UpdateRotation(deltaTime2);
		}

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



