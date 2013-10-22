#include "widget.h"
#include <QPainter>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::white);
}

void Widget::mouseMoveEvent(QMouseEvent *)
{
    static int i=0;
    qDebug() << i++;
}
