#include "renderwidget.h"
#include <QPainter>
#include <QtGui>
#include <QDebug>
using namespace VBGL;
using namespace glm;

RenderWidget::RenderWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setAutoFillBackground(false);
    setAutoBufferSwap(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(40);
}

void RenderWidget::updateCamera()
{
    float a_x = radians(rotation.x);
    float a_y = radians(rotation.y);
    vec3 eye = cameraRadius * vec3(sin(a_x) * cos(a_y), sin(a_y), cos(a_x) * cos(a_y));

    cam.setPosition(eye);
    cam.lookAt(glm::vec3(0,0,0));
    cam.updateProjectionMatrix();
    cam.updateMatrix();
}

void RenderWidget::initializeGL()
{
    glewInit();
    GLStateManager::setDefaultGLState();
    GLStateManager::setClearColor(0,0,0.2);

    cameraRadius = 30.0f;
    cam.setFov(5);
    cam.setNear(0.1);
    cam.setFar(10000.0);
    cam.setUp(glm::vec3(0, 1, 0));

    rotation = vec2(55, 35);
    updateCamera();

/*
    VTF::RefPointer<VBGL::Geometry> geo = new VBGL::Geometry;
    VTF::RefPointer<VBGL::Material> material = new MyMaterial;
    geo->verticesAppend(glm::vec3(0,0,0));
    geo->normalsAppend(glm::vec3(0,0,1));
    geo->verticesAppend(glm::vec3(1,0,0));
    geo->normalsAppend(glm::vec3(0,0,1));
    geo->verticesAppend(glm::vec3(0,1,0));
    geo->normalsAppend(glm::vec3(0,1,1));
    geo->verticesAppend(glm::vec3(1,1,0));
    geo->normalsAppend(glm::vec3(0,1,1));
    geo->verticesAppend(glm::vec3(0,1,-1));
    geo->normalsAppend(glm::vec3(0,1,0));
    geo->verticesAppend(glm::vec3(1,1,-1));
    geo->normalsAppend(glm::vec3(0,1,0));
    geo->indicesAppend(0);
    geo->indicesAppend(1);
    geo->indicesAppend(3);
    geo->indicesAppend(2);
    geo->indicesAppend(3);
    geo->indicesAppend(2);
    geo->indicesAppend(4);
    geo->indicesAppend(5);
    geo->setGLType(GL_QUADS);

    model = new VBGL::Mesh(geo, material);
    */
    m_model.reset();
    m_axis.reset();
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void RenderWidget::paintGL()
{
    GLStateManager::setClearColor(0,0,0.2);
    GLStateManager::clear();
    GLStateManager::enableDepthTest();
    GLStateManager::disableClipping();

    //static float time = 0;
    //time += 0.04;
    //model->setMatrix(glm::rotate(glm::mat4(), time*50, glm::vec3(0,0,1)));

    //model->draw(&cam);
    m_model.draw(&cam);
    swapBuffers();
}

void RenderWidget::mousePressEvent(QMouseEvent *me) {
    omp = me->pos();
}

void RenderWidget::mouseMoveEvent(QMouseEvent *me)
{
    QPoint d = me->pos() - omp;
    omp = me->pos();
    if (Qt::LeftButton == (me->buttons() & Qt::LeftButton))
    {
        //Left button move
        rotation.x += 0.1 * d.x();
        rotation.y -= 0.1 * d.y();
        updateCamera();
    }
    if (Qt::RightButton == (me->buttons() & Qt::RightButton))
    {
        //Right button move
    }
}

void RenderWidget::wheelEvent(QWheelEvent *me)
{
    int numDegrees = me->delta() / 8;
    int numSteps = numDegrees / 15;
    if (me->orientation() == Qt::Vertical)
    {
        //Scroll vertical = zoom camera
    }
    me->accept();
}
