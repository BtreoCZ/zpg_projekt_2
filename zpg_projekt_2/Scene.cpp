#include "Scene.h"

Scene::Scene(vector<DrawableObject>& drawableObjects, Camera* camera)
{
    this->camera = camera;
    this->objects = drawableObjects;
}

void Scene::Init(std::vector<DrawableObject>& drawableObjects,Camera *camera)
{
    this->camera = camera;
    for (const auto& object : drawableObjects)
    {
        this->objects.push_back(object);
    }
}

void Scene::Render()
{
    for (auto& object : objects)
    {
        object.Draw();
    }
}

void Scene::AddObject(DrawableObject object)
{
    objects.push_back(object);
}

Camera* Scene::GetCamera()
{
    return this->camera;
}
