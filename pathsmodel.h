#ifndef PATHSMODEL_H
#define PATHSMODEL_H

#include <VBGL/VBGL>

class PathsModel
{
    VTF::RefPointer<VBGL::Mesh> mesh;
public:
    PathsModel();
    void reset();
    void draw(VBGL::Camera* cam);
    void addPoint(glm::vec3);
    void clearPoints();
};

#endif // PATHSMODEL_H
