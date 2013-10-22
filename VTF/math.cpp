#include "math.h"
#include <iomanip>

using namespace glm;

vec3 VTF::positionFromMatrix(const mat4 &mat)
{
    return vec3(mat[3]);
}

vec3 VTF::scaleFromMatrix(const mat4 &mat)
{
    float dx = length(vec3(mat[0]));
    float dy = length(vec3(mat[1]));
    float dz = length(vec3(mat[2]));
    return vec3(dx,dy,dz);
}

quat VTF::quatFromRotationMatrix(const mat4 &mat)
{
    return quat(mat);
}

void VTF::computeTangentBasis(
        // inputs
        std::vector<glm::vec3> & vertices,
        std::vector<glm::vec2> & uvs,
        std::vector<glm::vec3> & normals,
        // outputs
        std::vector<glm::vec3> & tangents,
        std::vector<glm::vec3> & bitangents
        )
{
    if(vertices.size() < 3)
        return;
    assert((vertices.size() % 3) == 0);
    assert(vertices.size() == uvs.size());
    assert(uvs.size() == normals.size());
    for (unsigned int i=0; i<vertices.size(); i+=3 ){
        // Shortcuts for vertices
        glm::vec3 & v0 = vertices[i+0];
        glm::vec3 & v1 = vertices[i+1];
        glm::vec3 & v2 = vertices[i+2];

        // Shortcuts for UVs
        glm::vec2 & uv0 = uvs[i+0];
        glm::vec2 & uv1 = uvs[i+1];
        glm::vec2 & uv2 = uvs[i+2];

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        // Set the same tangent for all three vertices of the triangle.
        // They will be merged later, in vboindexer.cpp
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        // Same thing for binormals
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }

    // See "Going Further"
    for (unsigned int i=0; i<vertices.size(); i+=1 )
    {
        glm::vec3 & n = normals[i];
        glm::vec3 & t = tangents[i];
        glm::vec3 & b = bitangents[i];

        // Gram-Schmidt orthogonalize
        t = glm::normalize(t - n * glm::dot(n, t));

        // Calculate handedness
        if (glm::dot(glm::cross(n, t), b) < 0.0f){
            t = t * -1.0f;
        }
    }
}


std::ostream &operator<<(std::ostream &o, const vec2 &m)
{
    for(int i=0;i<2;++i) {
        o << std::setw(15) << m[i]<<" ";
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const vec3 &m)
{
    for(int i=0;i<3;++i) {
        o << std::setw(15) << m[i]<<" ";
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const vec4 &m)
{
    for(int i=0;i<4;++i) {
        o << std::setw(15) << m[i]<<" ";
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const mat4 &m)
{
    mat4 n=glm::transpose(m);
    for(int i=0;i<4;++i) {
        o << n[i]<< "\n";
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const mat3 &m)
{
    mat3 n=glm::transpose(m);
    for(int i=0;i<3;++i) {
        o << n[i]<< "\n";
    }
    return o;
}
