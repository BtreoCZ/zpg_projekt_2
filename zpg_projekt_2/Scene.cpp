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

void Scene::Render()
{
	if (skybox != nullptr)
    skybox->Draw();

    for (auto& object : objects)
    {
        object->Draw();
    }
}

void Scene::AddObject(DrawableObject* object)
{
    objects.push_back(object);
}

Camera* Scene::GetCamera()
{
    return this->camera;
}
