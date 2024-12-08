#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Skybox.h"
#include "tree.h"
using namespace std;

class Scene
{
public:
    std::vector<DrawableObject*> objects;
    Camera* camera;
	Skybox* skybox;
	vector<Light*> lights;

    Scene(vector<DrawableObject*> drawableObjects, Camera* camera);
    Scene(vector<DrawableObject*> drawableObjects, Camera* camera,Skybox* skybox);
    void Init(vector<DrawableObject*> drawableObjects,Camera* camera);

	Skybox* GetSkybox();
    void Render();
    void CreateTree(glm::vec3 position);

    void AddObject(DrawableObject* object);
	void AddLight(Light* light);
	void AddLights(vector<Light*> lights);

    Camera* GetCamera();
};