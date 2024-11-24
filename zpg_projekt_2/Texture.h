#pragma once
#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
	GLuint textureID;
	static int textureCount;
	GLuint image;
public:
	Texture();
	void LoadTexture(const char* filename);
	void BindTexture();
	GLuint GetTextureID();
};
