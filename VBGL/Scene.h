#pragma once

#include <VBGL/Object3D.h>
#include <VBGL/core/Core>
#include <VBGL/Mesh.h>
#include <functional>
#include <vector>
#include <set>

namespace VBGL
{

class Scene : public Object3D
{
    std::set<VTF::RefPointer<VBGL::Mesh> >
       meshes;
public:
    Scene();

    virtual void add(Object3D*);
    void add(VBGL::Mesh*);
    virtual void remove(Object3D*);
    void iterate(std::function<void(Mesh*)> func);
};

}
