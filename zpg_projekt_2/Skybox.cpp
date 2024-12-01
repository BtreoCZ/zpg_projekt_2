#include "Skybox.h"

Skybox::Skybox(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal, Camera* camera, std::vector<Light*> lights, Texture* texture) : DrawableObject(vertices, vertexSize, drawMode, vertexShader, fragmentShader, withNormal, camera, lights, texture)
{


};

Skybox::Skybox(Model* model, ShaderProgram* shaderProgram, Material* material) : DrawableObject(model, shaderProgram, material)
{

}
void Skybox::Update(Subject* subject)
{
	Camera* camera = (Camera*)subject;

	this->SetPosition(camera->GetPosition());
}

void Skybox::Draw()
{
    glDisable(GL_DEPTH_TEST);

    shaderProgram->UseProgram();

    shaderProgram->SetMatrix(transformation.GetMatrix());

    shaderProgram->SetMat3Uniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(transformation.GetMatrix()))));

    shaderProgram->SetFloatUniform("material.ra", this->material->GetAmbientCoefficient());

    shaderProgram->SetFloatUniform("material.rd", this->material->GetDiffuseCoefficient());

    shaderProgram->SetFloatUniform("material.rs", this->material->GetSpecularCoefficient());

    if (hasTexture)
    {
        shaderProgram->SetIntUniform("textureUnitID", texture->GetTextureID());

        model.BindVAO();

        shaderProgram->Draw();

        shaderProgram->DetachProgram();

        model.UnbindVAO();
    }
    else {

        model.BindVAO();

        shaderProgram->Draw();

        shaderProgram->DetachProgram();

        model.UnbindVAO();
    }
    glEnable(GL_DEPTH_TEST);
}

