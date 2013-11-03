#ifndef MODEL_H
#define MODEL_H

#include <VBGL/VBGL>

class ModelMaterial : public VBGL::Material
{
public:
    ModelMaterial();
};


class Model
{
    VTF::RefPointer<VBGL::Mesh> mesh;
    glm::ivec2 size;
public:
    Model();

    void resize(glm::ivec2 s, glm::vec3 O, glm::vec3 S);

    void setH(const std::vector<float>& Hs)
    {
        mesh->geometry()->heightValuesSet(Hs);
    }

    void setProblems(const std::vector<int>& Ps)
    {
        mesh->geometry()->vertexProblemsSet(Ps);
    }

    /*
    void setH(int x, int y, float d)
    {
        int idx = x*size.y+y;
        glm::vec3 v = mesh->geometry()->vertices(idx);
        v.z = d;
        if(v.z < 0)
            mesh->geometry()->vertexProblemsSet(idx, 1);
        mesh->geometry()->verticesSet(idx, v);
    }
    */

    void reset();
    void draw(VBGL::Camera* cam);

    glm::ivec2 getSize() const;
};

#endif // MODEL_H
