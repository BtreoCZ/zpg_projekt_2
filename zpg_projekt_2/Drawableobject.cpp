#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal,Camera *camera,Light* light)
{
    this->shaderProgram = new ShaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera,light);

    this->transformation = Transformation();

    if (withNormal)
        model.GenerateModel(vertices, vertexSize);
    else
        model.GenerateModelWithoutNormals(vertices, vertexSize);

    shaderProgram->AddShaders(vertexShader, fragmentShader);
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram) : shaderProgram(shaderProgram), model(*model)
{
    this->transformation = Transformation();
}


void DrawableObject::SetPosition(glm::vec3 position)
{
    transformation.AddComponent(new Translate(position));
}


void DrawableObject::SetRotation(glm::vec3 rotationDegrees)
{
    transformation.AddComponent(new Rotate(rotationDegrees));
}


void DrawableObject::SetScale(glm::vec3 scale)
{
    transformation.AddComponent(new Scale(scale));
}


void DrawableObject::Draw()
{

    
    shaderProgram->UseProgram();

    shaderProgram->SetMatrix(transformation.GetMatrix());
    shaderProgram->SetMat3Uniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(transformation.GetMatrix()))));

    model.BindVAO();

    shaderProgram->Draw();

    model.UnbindVAO();
}