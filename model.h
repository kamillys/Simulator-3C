#ifndef MODEL_H
#define MODEL_H

#include <VBGL/VBGL>

class MyMaterial : public VBGL::Material
{
public:
    MyMaterial();
};


class Model
{
    VTF::RefPointer<VBGL::Mesh> mesh;
public:
    Model();

    void resize(glm::vec3);

    void reset();
    void draw(VBGL::Camera* cam);
};

#endif // MODEL_H
