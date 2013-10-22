#pragma once

#include <VTF/Pointers>
#include "myGL.h"

namespace VBGL
{

class Texture2D : public VTF::RefObject
{
    GLuint texID;
public:
    Texture2D();
    ~Texture2D();

    void bind();
    void release();

    void setWrap(GLint horizontal, GLint vertical);
    void setMagFilter(GLint type);
    void setMinFilter(GLint type);
    void generateMipmap();

    void setDefaultParameters();
};

}
