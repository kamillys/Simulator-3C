#include "PerspectiveCamera.h"


VBGL::PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far):
    _fov(fov),
    _aspect(aspect),
    _near(near),
    _far(far),
    _width(0),
    _heigth(0),
    _hasFullWidth(false)
{
    updateProjectionMatrix();
}

void VBGL::PerspectiveCamera::updateProjectionMatrix()
{
    if (_hasFullWidth) {
        setProjectionMatrix(glm::perspectiveFov(_fov, _width, _heigth, _near, _far));
    } else {
        setProjectionMatrix(glm::perspective(_fov, _aspect, _near, _far));
    }
}

void VBGL::PerspectiveCamera::setLens(float focalLength, float frameHeight)
{
    _fov = 2 * glm::degrees(glm::atan(frameHeight / (focalLength * 2)));
    updateProjectionMatrix();
}

float VBGL::PerspectiveCamera::fov() const
{
    return _fov;
}

void VBGL::PerspectiveCamera::setFov(float fov)
{
    _fov = fov;
}

float VBGL::PerspectiveCamera::aspect() const
{
    return _aspect;
}

void VBGL::PerspectiveCamera::setAspect(float aspect)
{
    _aspect = aspect;
}

float VBGL::PerspectiveCamera::near() const
{
    return _near;
}

void VBGL::PerspectiveCamera::setNear(float near)
{
    _near = near;
}

float VBGL::PerspectiveCamera::far() const
{
    return _far;
}

void VBGL::PerspectiveCamera::setFar(float far)
{
    _far = far;
}

float VBGL::PerspectiveCamera::heigth() const
{
    return _heigth;
}

void VBGL::PerspectiveCamera::setHeigth(float heigth)
{
    _heigth = heigth;
    _hasFullWidth = true;
}

float VBGL::PerspectiveCamera::width() const
{
    return _width;
}

void VBGL::PerspectiveCamera::setWidth(float width)
{
    _width = width;
    _hasFullWidth = true;
}

void VBGL::PerspectiveCamera::cleanSize()
{
    _width = _heigth = 0;
    _hasFullWidth = false;
}

void VBGL::PerspectiveCamera::setSize(float width, float heigth)
{
    setWidth(width);
    setHeigth(heigth);
}

void VBGL::PerspectiveCamera::setSize(const glm::vec2 &size)
{
    setSize(size.x, size.y);
}
