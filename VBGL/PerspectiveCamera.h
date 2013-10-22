#pragma once

#include <VBGL/Camera.h>

namespace VBGL
{

class PerspectiveCamera : public Camera
{
    float _fov;
    float _aspect;
    float _near;
    float _far;

    float _width;
    float _heigth;
    bool _hasFullWidth;
public:
    PerspectiveCamera(float fov = 50, float aspect = 1,
                      float near = 0.1, float far = 2000);

    void updateProjectionMatrix();
    void setLens(float focalLength, float frameHeight = 24);

    float fov() const;
    void setFov(float fov);
    float aspect() const;
    void setAspect(float aspect);
    float near() const;
    void setNear(float near);
    float far() const;
    void setFar(float far);
    float width() const;
    void setWidth(float width);
    float heigth() const;
    void setHeigth(float heigth);
    void cleanSize();
    void setSize(float width, float heigth);
    void setSize(const glm::vec2& size);
};

}
