#include "grid.h"

Grid::Grid(){

}

void Grid::vertical(){
    for(float x=0; x<(X_RANGE/10); x+=0.1){
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex3f(x,0,0);
        glVertex3f(x,0,Y_RANGE/10);
        glEnd();
    }
}

void Grid::horizontal(){
    for(float z=0; z<(Y_RANGE/10)+0.1; z+=0.1){
    glBegin(GL_LINES);
    glColor3f(0,0,0);
        glVertex3f(0,0,z);
        glVertex3f(X_RANGE/10,0,z);
    glEnd();
    }
}
