#include "GLRenderer.h"

void VBGL::GLRenderer::render(VBGL::Scene *scene, VBGL::Camera *camera)
{
    GLStateManager::clear();

    camera->updateMatrix();

    scene->iterate([&](Mesh* m) {
        m->draw(camera);
    });
}
