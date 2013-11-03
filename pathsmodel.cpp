#include "pathsmodel.h"

class LineMaterial : public VBGL::Material
{
public:
    LineMaterial(){
        shader = new VBGL::ShaderProgram;
        shader->addShader("#version 130\n"
                          "attribute vec3 in_vertices;""\n"
                          "uniform mat4 UMVP;"
                          "void main(){""\n"
                          "gl_Position = UMVP * vec4(in_vertices, 1.0);"
                          "}""\n", VBGL::ShaderProgram::VertexShader);
        shader->addShader("#version 130\n"
                          "out vec4 val;""\n"
                          "void main(){""\n"
                          "val.a = 1;""\n"
                          "val.rgb = vec3(0,0,0);""\n"
                          "}""\n", VBGL::ShaderProgram::FragmentShader);
        shader->build();
    }
};

PathsModel::PathsModel()
{
}

void PathsModel::reset()
{
    mesh = new VBGL::Mesh(new VBGL::Geometry, new LineMaterial);
    mesh->geometry()->setGLType(GL_LINES);
}

void PathsModel::clearPoints()
{
    mesh->geometry()->verticesClear();
}

void PathsModel::addPoint(glm::vec3 pt)
{
    VBGL::Geometry* geo = mesh->geometry();
    if (geo->verticesCount() > 1)
        geo->verticesAppend(geo->vertices(geo->verticesCount()-1));
    geo->verticesAppend(pt);
}

void PathsModel::draw(VBGL::Camera *cam)
{
    mesh->draw(cam);
}
