#pragma once

#include <VTF/Pointers>
#include <VBGL/Camera.h>
#include <VBGL/Scene.h>

namespace VBGL {

class GLRenderer : VTF::RefObject
{
public:
    void render(Scene*, Camera*);
};

}
