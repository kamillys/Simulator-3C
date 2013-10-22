#include "originaxismodel.h"

using namespace glm;

class AxisMaterial : public VBGL::Material
{
public:
    glm::vec3 color;
    AxisMaterial(glm::vec3 _)
        : color(_)
    {
        shader = new VBGL::ShaderProgram;
        shader->addShader("#version 130\n"
                          "attribute vec3 in_vertices;""\n"
                          "attribute vec3 in_normals;""\n"
                          "out vec4 normals;"
                          "uniform mat4 UMVP;"
                          "uniform mat4 UNormalMatrix;"
                          "void main(){""\n"
                          "gl_Position = UMVP * vec4(in_vertices, 1.0);"
                          "normals = UNormalMatrix * vec4(normalize(in_normals), 0.0);"
                          "}""\n", VBGL::ShaderProgram::VertexShader);
        shader->addShader("#version 130\n"
                          "in vec4 normals;""\n"
                          "uniform vec3 color;""\n"
                          "void main(){""\n"
                          "color.a = 1;""\n"
                          "color.rgb = color;""\n"
                          "}""\n", VBGL::ShaderProgram::FragmentShader);
        shader->build();
    }

    void bind() {
        shader->setUniform("color", color);
    }
};

OriginAxisModel::OriginAxisModel()
{
}

static VTF::RefPointer<VBGL::Mesh> initAxis(glm::vec3 dir)
{
    VTF::RefPointer<VBGL::Geometry> g = new VBGL::Geometry;
    g->verticesAppend(vec3(0,0,0));
    g->verticesAppend(dir);
    g->verticesAppend(cross(vec3(0,0,0),dir));

    VTF::RefPointer<VBGL::Mesh> mesh = new VBGL::Mesh(g, new AxisMaterial(dir));
    return mesh;
}

void OriginAxisModel::reset()
{
    xMesh = initAxis(glm::vec3(1,0,0));
    yMesh = initAxis(glm::vec3(0,1,0));
    zMesh = initAxis(glm::vec3(0,0,1));
}

void OriginAxisModel::draw(VBGL::Camera *cam)
{
    xMesh->draw(cam);
    yMesh->draw(cam);
    zMesh->draw(cam);
}
