#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <VBGL/VBGL>
#include <QGLWidget>
#include <QGLBuffer>
#include <QTimer>

#include "model.h"
#include "originaxismodel.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT

    Model m_model;
    OriginAxisModel m_axis;
    VBGL::PerspectiveCamera cam;
    glm::vec2 rotation;
    float cameraRadius;

    void updateCamera();

private:
    QTimer timer;

public:
    explicit RenderWidget(QWidget *parent = 0);

signals:

public slots:
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
