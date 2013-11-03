#include "cuttermodel.h"
#include <QDebug>

using namespace glm;

class CutterMaterial : public VBGL::Material
{
public:
    CutterMaterial() {
        shader = new VBGL::ShaderProgram;
        shader->addShader("#version 130\n"
                          "attribute vec3 in_vertices;""\n"
                          "attribute vec3 in_normals;""\n"
                          "out vec4 normals;""\n"
                          "uniform mat4 UMV;""\n"
                          "uniform mat4 UMVP;""\n"
                          "uniform mat4 UNormalMatrix;""\n"
                          "uniform vec3 TPos;"
                          "void main(){""\n"
                          //"pos = in_vertices;""\n"
                          "gl_Position = UMVP * vec4(in_vertices+TPos, 1.0);""\n"
                          "normals = UNormalMatrix * vec4(normalize(in_normals), 0.0);""\n"
                          //"normals = vec4(in_normals, 0.0);""\n"
                          "}""\n", VBGL::ShaderProgram::VertexShader);

        shader->addShader("#version 130\n"
                          "in vec4 normals;"
                          "out vec4 fcolor;"
                          "void main(){""\n"
                          "vec3 lightDir = normalize(vec3(1,1,0));"
                          "vec3 N = normalize(normals.xyz);"
                          "float p = abs(dot(N,lightDir));"
                          "fcolor.rgb = p*vec3(0,1,0);"
                          "fcolor.a = 1;"
                          "}""\n", VBGL::ShaderProgram::FragmentShader);
        shader->build();
    }
};

CutterModel::CutterModel()
{
}

void CutterModel::reset(double w)
{
    w = 0.5*w;
    VTF::RefPointer<VBGL::Material> mat = new CutterMaterial;
    meshFlat = new VBGL::Mesh(new VBGL::Geometry, mat);
    meshRound = new VBGL::Mesh(new VBGL::Geometry, mat);
    //TODO: Init meshes
    VBGL::Geometry * geometry;

    const int VCOUNT = 10;
    const double dVCOUNT = 10.0;
    const int COUNT = 30;
    const double dCOUNT = 30.0;
    const double PI2 = (2.0 * M_PI);
    int beginidx;

    //Init flat
    geometry = meshFlat->geometry();
    geometry->verticesClear();
    geometry->normalsClear();
    geometry->indicesClear();
    //Bottom

    geometry->verticesAppend(vec3(0,0,0));
    geometry->normalsAppend(vec3(0,0,-1));

    for(int i=0;i<=COUNT;++i)
    {
        geometry->verticesAppend(vec3(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),0));
        geometry->normalsAppend(vec3(0,0,-1));
    }

    for(int i=0;i<COUNT;++i)
    {
        geometry->indicesAppend(0);
        geometry->indicesAppend(i+1);
        geometry->indicesAppend(i+2);
    }

    //Flat: cylinder
    beginidx = geometry->verticesCount();

    for(int i=0;i<=COUNT;++i)
    {
        geometry->verticesAppend(vec3(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),0));
        geometry->verticesAppend(vec3(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),1000000));

        vec3 N(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),0);
        N = normalize(N);
        geometry->normalsAppend(N);
        geometry->normalsAppend(N);
    }
    for(int i=0;i<COUNT;++i)
    {
        geometry->indicesAppend(beginidx+2*i+0);
        geometry->indicesAppend(beginidx+2*i+1);
        geometry->indicesAppend(beginidx+2*i+2);
        geometry->indicesAppend(beginidx+2*i+1);
        geometry->indicesAppend(beginidx+2*i+2);
        geometry->indicesAppend(beginidx+2*i+3);
    }
    //Init Round
    geometry = meshRound->geometry();
    geometry->verticesClear();
    geometry->normalsClear();
    geometry->indicesClear();

    for(int j=0;j<=VCOUNT;++j)
    {
        double r = j / dVCOUNT;
        for(int i=0;i<=COUNT;++i)
        {
            double x = w*r*sin(PI2*i/dCOUNT);
            double y = w*r*cos(PI2*i/dCOUNT);
            double z = w - sqrt(abs(w*w - x*x-y*y));
            //+ R - sqrt(abs(R*R-dist*dist))
            //Centre is in (0,0,w)
            //
            vec3 pos = vec3(x,y,z);
            geometry->verticesAppend(pos);
            geometry->normalsAppend(normalize(pos - vec3(0,0,w)));
        }
    }

    for(int j=0;j<VCOUNT;++j)
    {
        for(int i=0;i<COUNT;++i)
        {
            geometry->indicesAppend(j*(COUNT+1)+i+0);
            geometry->indicesAppend(j*(COUNT+1)+i+1);
            geometry->indicesAppend((j+1)*(COUNT+1)+i+0);
            geometry->indicesAppend(j*(COUNT+1)+i+1);
            geometry->indicesAppend((j+1)*(COUNT+1)+i+0);
            geometry->indicesAppend((j+1)*(COUNT+1)+i+1);
        }
    }


    //Round cylinder
    beginidx = geometry->verticesCount();

    for(int i=0;i<=COUNT;++i)
    {
        geometry->verticesAppend(vec3(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),w));
        geometry->verticesAppend(vec3(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),1000000));

        vec3 N(w*sin(PI2*i/dCOUNT),w*cos(PI2*i/dCOUNT),0);
        N = normalize(N);
        geometry->normalsAppend(N);
        geometry->normalsAppend(N);
    }
    for(int i=0;i<COUNT;++i)
    {
        geometry->indicesAppend(beginidx+2*i+0);
        geometry->indicesAppend(beginidx+2*i+1);
        geometry->indicesAppend(beginidx+2*i+2);
        geometry->indicesAppend(beginidx+2*i+1);
        geometry->indicesAppend(beginidx+2*i+2);
        geometry->indicesAppend(beginidx+2*i+3);
    }
}

void CutterModel::drawFlat(VBGL::Camera *cam)
{
    VBGL::ShaderProgram* s = meshFlat->material()->getShader();
    s->setUniform("TPos", pos);
    meshFlat->draw(cam);
}

void CutterModel::drawRound(VBGL::Camera *cam)
{
    VBGL::ShaderProgram* s = meshRound->material()->getShader();
    s->setUniform("TPos", pos);
    meshRound->draw(cam);
}


