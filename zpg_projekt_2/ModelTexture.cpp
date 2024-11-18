#include "ModelTexture.h"

ModelTexture::ModelTexture()
{
	this->VAO = 0;
	this->VBO = 0;
}

void ModelTexture::GenerateModel(const float* points)
{
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
}

void ModelTexture::BindVAO()
{
	glBindVertexArray(VAO);
}

void ModelTexture::UnbindVAO()
{
	glBindVertexArray(0);
}
