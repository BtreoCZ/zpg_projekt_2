#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Skybox.h"
using namespace std;

class Scene
{
public:
    std::vector<DrawableObject*> objects;
    Camera* camera;
	Skybox* skybox;

    Scene(vector<DrawableObject*> drawableObjects, Camera* camera);
    Scene(vector<DrawableObject*> drawableObjects, Camera* camera,Skybox* skybox);
    void Init(vector<DrawableObject*> drawableObjects,Camera* camera);

    void Render();

    void AddObject(DrawableObject* object);

    Camera* GetCamera();
};