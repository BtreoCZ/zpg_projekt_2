#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal, Camera* camera, std::vector<Light*> lights)
{
    // Initialize ShaderProgram with vector<Light*>
    this->shaderProgram = new ShaderProgram(
        drawMode,
        0,
        withNormal ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3,
        camera,
        lights  
    );

    this->transformation = Transformation();

    if (withNormal)
        model.GenerateModel(vertices, vertexSize);
    else
        model.GenerateModelWithoutNormals(vertices, vertexSize);

    shaderProgram->AddShaders(vertexShader, fragmentShader);
	id = idCounter++;
}

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal, Camera* camera, vector<Light*> lights, Texture* texture)
{
    // Initialize ShaderProgram with vector<Light*>
    this->shaderProgram = new ShaderProgram(
        drawMode,
        0,
        withNormal ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3,
        camera,
        lights
    );

    this->transformation = Transformation();

	this->texture = texture;
    if(withNormal){
	modelTexture.GenerateModel(vertices,vertexSize);
    }
    else {
        model.GenerateModelWithoutNormals(vertices, vertexSize);
    }

    this->hasTexture = true;

    shaderProgram->AddShaders(vertexShader, fragmentShader);
	id = idCounter++;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, Material* material) : shaderProgram(shaderProgram), model(*model), material(material)
{
    this->transformation = Transformation();
	id = idCounter++;
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

void DrawableObject::EnableDynamicRotation(float speed, const glm::vec3& axis)
{
    rotationSpeed = speed;
    rotationAxis = axis;
    isDynamicRotationEnabled = true;
}

void DrawableObject::UpdateRotation(float deltaTime)
{
    if (isDynamicRotationEnabled) {
        currentRotationAngle = rotationSpeed * deltaTime;

        SetRotation(rotationAxis * currentRotationAngle);
    }
}

void DrawableObject::setMaterial(Material* material)
{
	this->material = material;
}

void DrawableObject::setTexture(Texture* texture)
{
	this->texture = texture;
	this->hasTexture = true;
}

int DrawableObject::getID()
{
    return id;
}


void DrawableObject::Draw()
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

		modelTexture.BindVAO();

        shaderProgram->Draw();

		shaderProgram->DetachProgram();
		modelTexture.UnbindVAO();
	}else {

    model.BindVAO();

    shaderProgram->Draw();

	shaderProgram->DetachProgram();

    model.UnbindVAO();
    }
}