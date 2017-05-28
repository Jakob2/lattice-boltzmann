#ifndef WALL_H
#define WALL_H

#include "global.h"

class Wall
{
public:
    Wall();

    /*int xLow = 10;
    int xHigh = 20;
    int yLow = 8;
    int yHigh = 12;*/

    void setQuadVector(int xLow, int xHigh, int yLow, int yHigh);
    //void setQuadVector();
    static vector<vector<vector<int>>> quadVector;

    //void randomWall();
};

#endif // WALL_H
