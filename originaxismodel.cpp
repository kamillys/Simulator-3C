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
                          "out vec4 val;""\n"
                          "uniform vec3 color;""\n"
                          "void main(){""\n"
                          "val.a = 1;""\n"
                          "val.rgb = color;""\n"
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

static VTF::RefPointer<VBGL::Mesh> initAxis(int ax)
{
    glm::vec3 dir;
    dir[ax] = 1;
    int _X = 0, _Y = 0;
    switch(ax) {
    case 0: _X = 1; _Y = 2; break;
    case 1: _X = 2; _Y = 0; break;
    case 2: _X = 0; _Y = 1; break;
    }

    VTF::RefPointer<VBGL::Geometry> g = new VBGL::Geometry;
    float w = 0.05;
    static const int CNT = 10;
    std::vector<vec3> circle;
    for (int i=0;i<CNT;++i)
    {
        float X = w*sin(2.0*M_PI*i/(CNT));
        float Y = w*cos(2.0*M_PI*i/(CNT));
        vec3 v;
        v[ax] = w;
        v[_X] = X;
        v[_Y] = Y;
        circle.push_back(v);
    }
    for (int i=0;i<CNT;++i)
    {
        g->verticesAppend(dir);
        g->verticesAppend(circle[(i+1)%CNT]);
        g->verticesAppend(circle[i]);
    }


    VTF::RefPointer<VBGL::Mesh> mesh = new VBGL::Mesh(g, new AxisMaterial(dir));
    mesh->setScale(glm::vec3(100,100,100));
    mesh->setPosition(glm::vec3(-100,-100,-100));
    mesh->updateMatrix();
    return mesh;
}

void OriginAxisModel::reset()
{
    xMesh = initAxis(0);
    yMesh = initAxis(1);
    zMesh = initAxis(2);
}

void OriginAxisModel::draw(VBGL::Camera *cam)
{
    xMesh->draw(cam);
    yMesh->draw(cam);
    zMesh->draw(cam);
}
