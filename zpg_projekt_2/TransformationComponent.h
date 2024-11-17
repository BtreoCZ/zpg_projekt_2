#pragma once
#include <glm/glm.hpp>
class TransformationComponent
{
private:
    glm::mat4 matrix;
public:
    virtual glm::mat4 Apply(glm::mat4 model) = 0;
};

