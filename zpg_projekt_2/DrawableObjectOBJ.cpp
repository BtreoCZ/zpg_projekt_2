#include "DrawableObjectOBJ.h"

DrawableObjectOBJ::DrawableObjectOBJ(ModelOBJ* model, ShaderProgram* shaderProgram, Material* material) : DrawableObject(model, shaderProgram, material)
{
}

void DrawableObjectOBJ::Draw()
{
    shaderProgram->UseProgram();

    shaderProgram->SetMatrix(transformation.GetMatrix());

    shaderProgram->SetMat3Uniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(transformation.GetMatrix()))));

    shaderProgram->SetFloatUniform("material.ra", this->material->GetAmbientCoefficient());

    shaderProgram->SetFloatUniform("material.rd", this->material->GetDiffuseCoefficient());

    shaderProgram->SetFloatUniform("material.rs", this->material->GetSpecularCoefficient());

    if (hasTexture)
    {
        shaderProgram->SetIntUniform("textureUnitID", texture->GetTextureID());

        shaderProgram->SetIntUniform("hasTexture", 1);

        model.BindVAO();

        shaderProgram->DrawOBJ();

        shaderProgram->DetachProgram();

        model.UnbindVAO();
    }
    else {

        model.BindVAO();

        shaderProgram->DrawOBJ();

        shaderProgram->DetachProgram();

        model.UnbindVAO();
    }
}
