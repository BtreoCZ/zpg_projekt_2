#pragma once
#include "DrawableObject.h"
#include "ModelOBJ.h"
class DrawableObjectOBJ : public DrawableObject
{

public:
	DrawableObjectOBJ(ModelOBJ* model, ShaderProgram* shaderProgram, Material* material);
	virtual void Draw() override;
};

