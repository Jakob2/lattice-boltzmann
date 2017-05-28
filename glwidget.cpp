#include "glwidget.h"


GlWidget::GlWidget(QWidget * parent) : QGLWidget(parent){
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
    Lb lb;
    //this->lb.setQuadVector();
    //this->lb.initialize();
}

void GlWidget::initializeLB(){
    if(LB_INIT){
        //this->lb.setQuadVector();
        this->lb.setQuadVector(X_LOW, X_HIGH, Y_LOW, Y_HIGH);
        this->lb.initialize();
        LB_INIT = 0;
    }
}

void GlWidget::initializeGL(){
    glClearColor(0.5,0.5,0.5,1);
    glEnable(GL_DEPTH_TEST);
}

void GlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resizeGL(WIDTH, HEIGHT);
    glScalef(0.3,0.3,0.3);
    vertical();
    horizontal();
    initializeLB();
    for(int x=0; x<X_RANGE; x++){
        for(int y=0; y<Y_RANGE; y++){
            this->lb.setDensity(this->lb.getPoints(x,y));
            this->lb.setSpeed(this->lb.getPoints(x,y), x);
            this->lb.setEquilibrium(this->lb.getPoints(x,y));
            this->lb.setRelax(this->lb.getPoints(x,y));
        }
    }
    this->lb.stream(lb.points);
    STEP == 0 ? STEP = 1 : STEP = 0;
}

void GlWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(0.0, (float)w/(float)h, 0.01, 100.0);
    gluLookAt(0.0,0.0,0.0, 0.5,1.0,0.5, 0,1,0);
}
