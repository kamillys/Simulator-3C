#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);

};

#endif // WIDGET_H
