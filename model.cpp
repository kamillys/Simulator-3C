#include "model.h"

Model::Model()
{
}

void Model::resize(glm::vec3)
{
}

void Model::reset()
{
    VTF::RefPointer<VBGL::Geometry> geometry = new VBGL::Geometry;
    VTF::RefPointer<VBGL::Material> material = new MyMaterial;

    geometry->verticesAppend(glm::vec3(1,0,0));
    geometry->verticesAppend(glm::vec3(1,1,0));
    geometry->verticesAppend(glm::vec3(0,1,0));
    geometry->verticesAppend(glm::vec3(0,0,0));
    geometry->normalsAppend(glm::vec3(0,0,1));
    geometry->normalsAppend(glm::vec3(0,0,1));
    geometry->normalsAppend(glm::vec3(0,0,1));
    geometry->normalsAppend(glm::vec3(0,0,1));
    geometry->indicesAppend(0);
    geometry->indicesAppend(1);
    geometry->indicesAppend(2);
    geometry->indicesAppend(0);
    geometry->indicesAppend(2);
    geometry->indicesAppend(3);

    mesh = new VBGL::Mesh(geometry, material);
}

void Model::draw(VBGL::Camera *cam)
{
    mesh->draw(cam);
}


MyMaterial::MyMaterial(){
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
                      //"normals = vec4(in_normals, 0.0);"
                      "}""\n", VBGL::ShaderProgram::VertexShader);
    shader->addShader("#version 130\n"
                      "out vec4 color;""\n"
                      "in vec4 normals;""\n"
                      "void main(){""\n"
                      //"color = vec4(1,0,0,1);""\n"
                      //"color.rgb = (normals*0.5+0.5).rgb;"
                      "color.a = 1;"
                      "color.rgb = vec3(1,0,0);"
                      "}""\n", VBGL::ShaderProgram::FragmentShader);
    shader->build();
}
