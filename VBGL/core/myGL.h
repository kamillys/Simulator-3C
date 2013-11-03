#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#undef __GLEW_H__
#include <QGLWidget>
#include <iostream>
#include <VTF/Exception>

#include <VTF/Math>

/*
 * Graphic exception types
 */
namespace VTF{
EXCEPTION(GraphicsException);
#define THROW_GRAPHICS_EXCEPTION(msg) THROW_EXCEPTION_T(msg, VTF::GraphicsException)
EXCEPTION_S(ShaderBuildException, GraphicsException);
}

#define CHECK_GL_ERRORS(msg) \
do { \
    int glerror; \
    glerror = glGetError(); \
    if (glerror != GL_NO_ERROR) {\
        std::cerr << msg << ":" << gluErrorString(glerror) << "\n"; \
    THROW_GRAPHICS_EXCEPTION(msg) \
    } \
} while(0)

#define CHECH_GL_ERRORS_CRIT(msg) \
do { \
    int glerror; \
    glerror = glGetError(); \
    if (glerror != GL_NO_ERROR){ \
        THROW_GRAPHICS_EXCEPTION(msg) \
    } \
} while(0)

template<typename T>
struct GLSizeInfo;

#define GLSIZEINFOSTRUCT(type, vecLen, GLType) \
template<> \
struct GLSizeInfo<type> { \
    static const int vectorLength = vecLen; \
    static const int glType = GLType; \
};

GLSIZEINFOSTRUCT(int,        1, GL_INT)
GLSIZEINFOSTRUCT(glm::ivec1, 1, GL_INT)
GLSIZEINFOSTRUCT(glm::ivec2, 2, GL_INT)
GLSIZEINFOSTRUCT(glm::ivec3, 3, GL_INT)
GLSIZEINFOSTRUCT(glm::ivec4, 4, GL_INT)
GLSIZEINFOSTRUCT(float,     1, GL_FLOAT)
GLSIZEINFOSTRUCT(glm::vec1, 1, GL_FLOAT)
GLSIZEINFOSTRUCT(glm::vec2, 2, GL_FLOAT)
GLSIZEINFOSTRUCT(glm::vec3, 3, GL_FLOAT)
GLSIZEINFOSTRUCT(glm::vec4, 4, GL_FLOAT)

#undef GLSIZEINFOSTRUCT
