#pragma once

#include <VBGL/core/Core>
#include <VBGL/Object3D.h>
#include <VBGL/Camera.h>
#include <VBGL/Material.h>

namespace VBGL
{

class Mesh : public Object3D
{
    VTF::RefPointer<Geometry> _geometry;
    VTF::RefPointer<Material> _material;
public:
    Mesh(Geometry*, Material*);
    Geometry* geometry();
    Material* material();

    void draw(Camera* cam);
    void draw(Camera* cam, Material* _material);
};

}
