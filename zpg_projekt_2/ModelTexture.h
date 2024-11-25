#pragma once
#include "Model.h"
class Model;
class ModelTexture : public Model
{
public:
    GLuint VBO;
    GLuint VAO;

    ModelTexture();

    void GenerateModel(const float* points, GLsizeiptr size);

    void BindVAO();

    void UnbindVAO();

};

