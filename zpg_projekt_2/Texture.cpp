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
    glActiveTexture(GL_TEXTURE+textureID);
    GLuint image = SOIL_load_OGL_texture("wooden_fence.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (image == NULL) {
        printf("An error occurred while loading image.");
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);
}
