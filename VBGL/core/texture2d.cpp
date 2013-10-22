#include "texture2d.h"

using namespace VBGL;

Texture2D::Texture2D()
{
    glGenTextures(1, &texID);
    CHECK_GL_ERRORS("Texture2D generate");
}

Texture2D::~Texture2D()
{
    release();
    glDeleteTextures(1, &texID);
    CHECK_GL_ERRORS("Texture2D deleting");
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, texID);
    CHECK_GL_ERRORS("Texture2D binding");
}

void Texture2D::release()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrap(GLint horizontal, GLint vertical)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, horizontal);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vertical);
    CHECK_GL_ERRORS("Texture2D setWrap");
}

void Texture2D::setMagFilter(GLint type)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
    CHECK_GL_ERRORS("Texture2D setMagFilter");
}

void Texture2D::setMinFilter(GLint type)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
    CHECK_GL_ERRORS("Texture2D setMinFilter");
}

void Texture2D::generateMipmap()
{
    bind();
    glGenerateMipmap(GL_TEXTURE_2D);
    CHECK_GL_ERRORS("Texture2D generateMipmap");
}

void Texture2D::setDefaultParameters()
{
    setWrap(GL_CLAMP, GL_CLAMP);
    setMagFilter(GL_NEAREST);
    setMinFilter(GL_NEAREST);
    generateMipmap();
}
