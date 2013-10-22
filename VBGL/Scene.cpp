#include "Scene.h"
#include <iostream>


VBGL::Scene::Scene()
{
}

void VBGL::Scene::add(VBGL::Object3D * obj)
{
    std::cout << "Adding to scene!" << std::endl;
    VBGL::Object3D::add(obj);
    //TODO:
    //if is light
    //add to lights array

    //else if not camera and not bone
    //add to objects

    //add to scene each child
}

void VBGL::Scene::add(VBGL::Mesh * g)
{
    if (!g)
        return;
    meshes.insert(g);
}

void VBGL::Scene::remove(VBGL::Object3D *obj)
{
    VBGL::Object3D::remove(obj);
    //TODO:
    //remove object and its children
}

void VBGL::Scene::iterate(std::function<void (VBGL::Mesh *)> func)
{
    for(VTF::RefPointer<Mesh> m : meshes)
    {
        func(m);
    }
}


