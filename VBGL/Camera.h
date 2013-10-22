#pragma once

#include <VBGL/Object3D.h>

namespace VBGL
{

class Camera : public Object3D
{
    glm::mat4 _matrixWorldInverse;
    glm::mat4 _projectionMatrix;
    glm::mat4 _projectionMatrixInverse;

public:
    void lookAt(const glm::vec3& point);

    glm::mat4 matrixWorldInverse() const;
    glm::mat4 projectionMatrix() const;
    glm::mat4 projectionMatrixInverse() const;
    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
};

}
