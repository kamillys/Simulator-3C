#include "Mesh.h"


VBGL::Mesh::Mesh(VBGL::Geometry * g, VBGL::Material * m) :
    _geometry(g),
    _material(m)
{
    assert(g);
    assert(m);
}

VBGL::Geometry *VBGL::Mesh::geometry()
{
    return _geometry;
}

VBGL::Material *VBGL::Mesh::material()
{
    return _material;
}

void VBGL::Mesh::draw(VBGL::Camera *cam, VBGL::Material *_material)
{
    if(_material == NULL)
        _material = this->_material;
    _geometry->updateBuffers();
    glm::mat4 Proj = cam->projectionMatrix();
    //Proj[2][3] = 1;
    //std::cerr << Proj << "\n#####################\n\n";
    glm::mat4 View = glm::scale(glm::mat4(), glm::vec3(1,1,1))
            * glm::translate(glm::mat4(), glm::vec3(0,0,-2))
            * cam->matrixWorld();
    glm::mat4 Model = matrixWorld();

    glm::mat4 MV = View * Model;
    glm::mat4 MVP = Proj * MV;
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(Model));

    ShaderProgram* shader = _material->getShader();
    _material->bind();

    shader->setUniform("UMVP", MVP);
    shader->setUniform("UMod", Model);
    shader->setUniform("UNormalMatrix", NormalMatrix);

    if(_geometry->indicesCount() > 0)
        _geometry->indicedDraw(shader);
    else
        _geometry->draw(shader);
    shader->release();
}

void VBGL::Mesh::draw(VBGL::Camera *cam)
{
    draw(cam, _material);
}

