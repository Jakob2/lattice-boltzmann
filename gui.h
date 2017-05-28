#ifndef GUI_H
#define GUI_H

#include "global.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QDialog>

class Gui : public QDialog, public Ui::MainWindow
{
    Q_OBJECT
public:
    Gui();

    void connectGUI();

public slots:
    void chooseInletSpeed();
    void chooseVisualisation();
    void reset();
    void randomWall();

private:
    //GlWidget view;
};

#endif // GUI_H
