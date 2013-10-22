#pragma once

/* Using GLM library for math. */
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>


namespace VTF
{

glm::vec3 positionFromMatrix(const glm::mat4& mat);
glm::vec3 scaleFromMatrix(const glm::mat4& mat);
glm::quat quatFromRotationMatrix(const glm::mat4& mat);

/** From http://www.opengl-tutorial.org/ **/
/** Under WTFPL Public Licence **/
/**
 * To compute tangent you need to pass vertices, UVs and normals.
 * Simple.
**/
void computeTangentBasis(
        // inputs
        std::vector<glm::vec3> & vertices,
        std::vector<glm::vec2> & uvs,
        std::vector<glm::vec3> & normals,
        // outputs
        std::vector<glm::vec3> & tangents,
        std::vector<glm::vec3> & bitangents
);


}


std::ostream& operator<<(std::ostream& o, const glm::vec2& m);
std::ostream& operator<<(std::ostream& o, const glm::vec3& m);
std::ostream& operator<<(std::ostream& o, const glm::vec4& m);

std::ostream& operator<<(std::ostream& o, const glm::mat3& m);
std::ostream& operator<<(std::ostream& o, const glm::mat4& m);
