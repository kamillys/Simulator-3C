#include "Camera.h"


void VBGL::Camera::lookAt(const glm::vec3 &point)
{
    glm::mat4 m (glm::lookAt(point, position(), up()));
    setQuaternion(glm::quat(m));
}

glm::mat4 VBGL::Camera::projectionMatrixInverse() const
{
    return _projectionMatrixInverse;
}

glm::mat4 VBGL::Camera::projectionMatrix() const
{
    return _projectionMatrix;
}

void VBGL::Camera::setProjectionMatrix(const glm::mat4 &projectionMatrix)
{
    _projectionMatrix = projectionMatrix;
    _projectionMatrixInverse = glm::inverse(_projectionMatrix);
}

glm::mat4 VBGL::Camera::matrixWorldInverse() const
{
    return _matrixWorldInverse;
}
