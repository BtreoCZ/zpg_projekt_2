#include "Scene.h"

Scene::Scene(vector<DrawableObject*> drawableObjects, Camera* camera)
{
    this->camera = camera;
    this->objects = drawableObjects;

    camera->Notify();
}

Scene::Scene(vector<DrawableObject*> drawableObjects, Camera* camera, Skybox* skybox)
{
	this->camera = camera;
	this->objects = drawableObjects;
	this->skybox = skybox;

	camera->Notify();

}

void Scene::Init(std::vector<DrawableObject*> drawableObjects,Camera *camera)
{
    this->camera = camera;
    this->objects = drawableObjects;
}

Skybox* Scene::GetSkybox()
{
    return this->skybox;
}

void Scene::Render()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	if (skybox != nullptr){
        glStencilFunc(GL_ALWAYS, skybox->getID(), 0xFF);
        skybox->Draw();
    }

    for (auto& object : objects)
    {
        glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);
        object->Draw();
    }
}

void Scene::CreateTree(glm::vec3 position)
{
    Model* tree_model = new Model();
    tree_model->GenerateModel(tree, sizeof(tree));


    ShaderProgram* shader_tree = new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6, this->GetCamera(), lights);
    shader_tree->AddShaders("vertex.txt", "phong_lights.txt");

    Material* treeMaterial = new Material(0.4f, 0.6f, 0.1f);

    DrawableObject* treeObject = new DrawableObject(tree_model, shader_tree, treeMaterial);
	treeObject->SetPosition(position);
	treeObject->SetScale(glm::vec3(0.1f));
	this->AddObject(treeObject);
}

void Scene::AddObject(DrawableObject* object)
{
    objects.push_back(object);
}

void Scene::AddLight(Light* light)
{
	lights.push_back(light);
}

void Scene::AddLights(vector<Light*> lights)
{
	for (auto light : lights) {
		this->lights.push_back(light);
	}
}

Camera* Scene::GetCamera()
{
    return this->camera;
}
