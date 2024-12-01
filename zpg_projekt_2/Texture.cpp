#include "Texture.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

void Texture::LoadCubeMap(vector<string>& filePaths)
{
	this->textureID = Texture::textureCount;
	Texture::textureCount++;

    glActiveTexture(GL_TEXTURE0 + textureID);

    //this->image = SOIL_load_OGL_cubemap(
    //    filePaths[0].c_str(),
    //    filePaths[1].c_str(),
    //    filePaths[2].c_str(),
    //    filePaths[3].c_str(),
    //    filePaths[4].c_str(),
    //    filePaths[5].c_str(),
    //    SOIL_LOAD_RGB,
    //    SOIL_CREATE_NEW_ID,
    //    SOIL_FLAG_MIPMAPS
    //);

    this->image = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

    if (this->image == NULL) {
        cerr << "SOIL_load_OGL_cubemap error: " << SOIL_last_result() << endl;
        exit(EXIT_FAILURE);
    }

	glBindTexture(GL_TEXTURE_CUBE_MAP, this->image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}


GLuint Texture::GetTextureID()
{
	return this->textureID;
}
