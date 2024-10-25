#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
using namespace std;

class Scene
{
public:
    std::vector<DrawableObject> objects;
    Camera* camera;

    Scene(vector<DrawableObject>& drawableObjects, Camera* camera);
    void Init(vector<DrawableObject>& drawableObjects,Camera* camera);

    void Render();

    void AddObject(DrawableObject object);

    Camera* GetCamera();
};