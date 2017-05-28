#include "global.h"
#include "mainwindow.h"
#include "gui.h"
#include <QApplication>

int WIDTH = 671;
int HEIGHT = 261;
int X_RANGE = 40;
int Y_RANGE = 20;
const int Q = 9;
int STEP = 1;
double LR_SPEED = 1.0;
int VISUAL = 0;
int LB_INIT = 1;
int X_LOW = 10;
int X_HIGH = 20;
int Y_LOW = 8;
int Y_HIGH = 12;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    MainWindow *w = new MainWindow;
    Gui gui;
    gui.setupUi(w);
    gui.connectGUI();
    w->show();



    return a.exec();
}
