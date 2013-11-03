#ifndef CUTTERMODEL_H
#define CUTTERMODEL_H

#include <VBGL/VBGL>

class CutterModel
{
    VTF::RefPointer<VBGL::Mesh> meshFlat;
    VTF::RefPointer<VBGL::Mesh> meshRound;
    glm::vec3 pos;
public:
    CutterModel();
    void reset(double w);
    void drawFlat(VBGL::Camera* cam);
    void drawRound(VBGL::Camera* cam);
    void setPosition(glm::vec3 p) { pos = p; }
};

#endif // CUTTERMODEL_H
