#pragma once
#include "Model.h"
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include <iostream>
struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};
class ModelOBJ : public Model
{
	int indicesCount;
    
public:
    GLuint IBO;
	ModelOBJ();
	void GenerateModelOBJ(const char* filename);
	int GetIndicesCount();
};

