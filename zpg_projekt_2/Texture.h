#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <vector>
#include <string>
using namespace std;
class Texture
{
	GLuint textureID;
	static int textureCount;
	GLuint image;
public:
	Texture();
	void LoadTexture(const char* filename);
	void BindTexture();
	void LoadCubeMap(vector<string>& filePaths);
	GLuint GetTextureID();
};
