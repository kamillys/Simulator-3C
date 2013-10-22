#ifndef ORIGINAXISMODEL_H
#define ORIGINAXISMODEL_H

#include <VBGL/VBGL>

class OriginAxisModel
{
    VTF::RefPointer<VBGL::Mesh> xMesh;
    VTF::RefPointer<VBGL::Mesh> yMesh;
    VTF::RefPointer<VBGL::Mesh> zMesh;
public:
    OriginAxisModel();
    void reset();
    void draw(VBGL::Camera* cam);
};

#endif // ORIGINAXISMODEL_H
