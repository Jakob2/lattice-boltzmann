#include "gui.h"

Gui::Gui(){
    //GlWidget view;
}

void Gui::connectGUI(){
    QObject::connect(doubleSpinBox_inlet, SIGNAL(valueChanged(double)), this, SLOT(chooseInletSpeed()));
    QObject::connect(comboBox_visual, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseVisualisation()));
    QObject::connect(pushButton_reset, SIGNAL(pressed()), this, SLOT(reset()));
    QObject::connect(pushButton_random, SIGNAL(pressed()), this, SLOT(randomWall()));
}

void Gui::chooseInletSpeed(){
    LR_SPEED = doubleSpinBox_inlet->value();
    cout<<"LR_SPEED: "<<LR_SPEED<<endl;
}

void Gui::chooseVisualisation(){
    VISUAL = comboBox_visual->currentIndex();
}

void Gui::reset(){
    LB_INIT = 1;
}

void Gui::randomWall(){
    srand (time(NULL));
    X_HIGH = rand() % (X_RANGE-3) +2;
    X_LOW = rand() % (X_HIGH-4) +2;
    Y_HIGH = rand() % (Y_RANGE-3) +2;
    Y_LOW = rand() % (Y_HIGH-4) +2;
}
