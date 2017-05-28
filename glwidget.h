#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "global.h"
#include "grid.h"
#include "lb.h"
#include <QGLWidget>
#include <QTimer>

class GlWidget : public QGLWidget, public Grid, public Lb
{
public:
    explicit GlWidget(QWidget * parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;
    Lb lb;
    void initializeLB();
};

#endif // GLWIDGET_H
