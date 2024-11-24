#include "Texture.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

Texture::Texture()
{
	this->textureID = 0;
}

void Texture::LoadTexture(const char* filename)
{
    this->textureID = Texture::textureCount;
    Texture::textureCount++;

    glActiveTexture(GL_TEXTURE0+textureID);
     this->image = SOIL_load_OGL_texture(filename, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (this->image == NULL) {
        printf("An error occurred while loading image.");
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, this->image);
}

void Texture::BindTexture()
{
	glActiveTexture(GL_TEXTURE0 + textureID);

	glBindTexture(GL_TEXTURE_2D, this->image);
}


GLuint Texture::GetTextureID()
{
	return this->textureID;
}
