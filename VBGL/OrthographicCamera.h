#pragma once

#include <VBGL/Camera.h>

namespace VBGL
{

class OrtographicCamera : public Camera
{
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;
public:
    OrtographicCamera(float l, float r, float t, float b, float n=0.1, float f=2000)
        :left(l), right(r), top(t), bottom(b), near(n), far(f)
    {
        glm::mat4 m = glm::ortho(left, right, bottom, top, near, far);
        setProjectionMatrix(m);
    }
};

}
