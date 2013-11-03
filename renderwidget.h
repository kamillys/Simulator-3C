#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <VBGL/VBGL>

#include <QTimer>
#include "cuttersettingsform.h"

#include "model.h"
#include "originaxismodel.h"
#include "pathsmodel.h"
#include "cuttermodel.h"

#include "cutterlogic.h"

#include "Paths/commands.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT

    CutterModel m_cutter;
    Model m_model;
    OriginAxisModel m_axis;
    PathsModel m_paths; //For displaying paths
    bool showPaths = true;

    CutterLogic logic;

    VBGL::PerspectiveCamera cam;
    glm::vec2 rotation;
    glm::vec3 camPosition;
    float cameraRadius;

    enum class AnimationStatus
    {
        Stopped,
        Playing,
        Paused
    } anistat = AnimationStatus::Stopped;

    void updateCamera();

private:
    QTimer timer;

    void copyHM();
public:
    explicit RenderWidget(QWidget *parent = 0);

signals:
    void animStopped();
    void animStarted();
    void animPaused();
    void animResumed();
    void animResetted();

public slots:
    void resizeCutter(float w);
    void resizeMaterial(glm::ivec2 d, glm::vec3 o, glm::vec3 s);
    void parseCommands(const CNCCommandList& commands);

    void moveCutter(glm::vec3 p);

    void updateAnimation();
    void startAnimation();
    void stopAnimation();
    void resumeAnimation();
    void pauseAnimation();
    void resetAnimation();

    void setAnimationSteps(int _);

    void skipAnimation();

    void setShowingPaths(bool _);

    void cutterChanged(CutterType type, double diameter);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    QPoint omp;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

};

#endif // RENDERWIDGET_H
