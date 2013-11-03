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
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    connect(&logic, SIGNAL(moveCutter(glm::vec3)), this, SLOT(moveCutter(glm::vec3)));
    timer.setInterval(40);
}

void RenderWidget::resizeCutter(float w)
{
    m_cutter.reset(w);
}

void RenderWidget::resizeMaterial(ivec2 d, vec3 o, vec3 s)
{
    m_model.resize(d,o,s);
    logic.size = s;
    logic.origin = o;
    logic.resizeHM(d.x,d.y);
    updateGL();
}

void RenderWidget::parseCommands(const CNCCommandList &commands)
{
    m_paths.clearPoints();
    logic.path.clear();
    foreach(const CNCCommand& c, commands)
    {
        if(c.type == CNCType::Move)
        m_paths.addPoint(glm::vec3(c.data));
        logic.path.append(c.data);
    }
    updateGL();
}

void RenderWidget::moveCutter(vec3 p)
{
    m_cutter.setPosition(p);
    updateGL();
}

void RenderWidget::copyHM()
{
    m_model.setH(logic.heightMap);
    m_model.setProblems(logic.problemMap);
    /*
    for(int i=0;i<logic.heightMap.size();++i)
        for(int j=0;j<logic.heightMap[i].size();++j)
        {
            m_model.setH(i,j,logic.heightMap[i][j]);
        }
    */
}

void RenderWidget::startAnimation()
{
    qDebug() << "Animation start";
    logic.initL();
    anistat = AnimationStatus::Playing;
    emit animStarted();
    timer.start();
}

void RenderWidget::pauseAnimation()
{
    qDebug() << "Animation pause";
    anistat = AnimationStatus::Paused;
    timer.stop();
    emit animPaused();
}

void RenderWidget::resetAnimation()
{
    qDebug() << "Animation reset";
    timer.stop();
    anistat = AnimationStatus::Stopped;
    emit animResetted();
}

void RenderWidget::setAnimationSteps(int _)
{
    logic.steps = _;
}

void RenderWidget::skipAnimation()
{
    logic.skip = true;
    updateAnimation();
    logic.skip = false;
}

void RenderWidget::setShowingPaths(bool _)
{
    showPaths = _;
    updateGL();
}

void RenderWidget::cutterChanged(CutterType type, double diameter)
{
    resetAnimation();
    if (type == CutterType::Round) logic.Round = true;
    else logic.Round = false;

    logic.cutterDiameter = diameter;
    m_cutter.reset(diameter);

    updateGL();
}

void RenderWidget::resumeAnimation()
{
    qDebug() << "Animation resume";
    anistat = AnimationStatus::Playing;
    timer.start();
    emit animResumed();
}

void RenderWidget::stopAnimation()
{
    qDebug() << "Animation stop";
    anistat = AnimationStatus::Stopped;
    timer.stop();
    moveCutter(glm::vec3(0,0,100));
    emit animStopped();
}

void RenderWidget::updateAnimation()
{
    //qDebug() << "Animation frame";
    bool stopped;
    if(logic.step(&stopped, logic.steps))
    {
        copyHM();
        updateGL();
    }
    if(stopped)
        stopAnimation();
}

void RenderWidget::updateCamera()
{
    static const float eps = 10e-3;
    if (cameraRadius < eps)
        cameraRadius = eps;

    rotation.y = clamp(rotation.y, -89.0f, 89.0f);
    float a_x = radians(rotation.x);
    float a_y = radians(rotation.y);
    //TODO: Make eye rotateable in good way :DD
    vec3 eye = camPosition - cameraRadius * vec3(sin(a_x) * cos(a_y), cos(a_x) * cos(a_y), sin(a_y));

    cam.setPosition(eye);
    cam.lookAt(camPosition);
    cam.updateProjectionMatrix();
    cam.updateMatrix();
}

void RenderWidget::initializeGL()
{
    glewInit();
    GLStateManager::setDefaultGLState();
    GLStateManager::setClearColor(0,0,0.2);

    cameraRadius = 10000.0f;
    cam.setFov(5);
    cam.setNear(100.0);
    cam.setFar(1000000.0);
    cam.setUp(glm::vec3(0, 0, 1));

    rotation = vec2(55, 35);
    updateCamera();

    m_model.reset();
    m_axis.reset();
    m_paths.reset();
    resizeCutter(14);

    logic.origin = glm::vec3(-50,-75,0);
    logic.size = vec3(100,150,50);
    moveCutter(glm::vec3(0,0,100.0));

    logic.resizeHM(m_model.getSize().x,
                   m_model.getSize().y);
}

void RenderWidget::resizeGL(int w, int h)
{
    if (h==0) h=1;
    glViewport(0,0,w,h);
    cam.setAspect(float(w)/float(h));
    updateCamera();
}

void RenderWidget::paintGL()
{
    GLStateManager::clear();
    GLStateManager::disableClipping();

    m_model.draw(&cam);
    m_axis.draw(&cam);
    if (showPaths)
        m_paths.draw(&cam);

    if (logic.Round)
        m_cutter.drawRound(&cam);
    else
        m_cutter.drawFlat(&cam);

    //Draw Depth Buffer

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
        //Left button move: Rotate
        rotation.x += 0.2 * d.x();
        rotation.y += 0.1 * d.y();
        updateCamera();
        updateGL();
    }
    if (Qt::RightButton == (me->buttons() & Qt::RightButton))
    {
        //Right button move: move cam

        //TODO: Translation
        float a_x = radians(rotation.x);
        float a_y = radians(rotation.y);
        vec3 eye = camPosition + cameraRadius * vec3(sin(a_x) * cos(a_y), cos(a_x) * cos(a_y), sin(a_y));
        vec3 eye_dir = camPosition - eye;
        vec3 up(0, 0, 1);
        vec3 right = cross(eye_dir, up);
        up = cross(right, eye_dir);
        //now: translate pos by up/right scaled
        float scalex = 0.0003;
        float scaley = -0.0000001;
        camPosition += d.y() * scaley * up + d.x() * scalex * right;

        updateCamera();
        updateGL();
    }
}

void RenderWidget::wheelEvent(QWheelEvent *me)
{
    int numDegrees = me->delta() / 8;
    int numSteps = numDegrees / 15;
    if (me->orientation() == Qt::Vertical)
    {
        //Scroll vertical = zoom camera
        float scale = 100;
        cameraRadius += numSteps * scale;
        updateCamera();
        updateGL();
    }
    me->accept();
}
