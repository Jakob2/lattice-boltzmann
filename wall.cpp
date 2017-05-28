#include "wall.h"



vector<vector<vector<int>>> Wall::quadVector;

Wall::Wall(){

}

//void Wall::setQuadVector(){
void Wall::setQuadVector(int xLow, int xHigh, int yLow, int yHigh){
    /*int xLow, xHigh, yLow, yHigh;
    xLow = 10;
    xHigh = 20;
    yLow = 8;
    yHigh = 12;*/
    Wall::quadVector.clear();
    Wall::quadVector.resize(X_RANGE);
    for(int i=0; i<X_RANGE; i++){
        Wall::quadVector[i].resize(Y_RANGE);
    }

    for(int x=0; x<X_RANGE; x++){
        for(int y=0; y<Y_RANGE; y++){
            if(y==0 || y==Y_RANGE-1)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xLow && y == yLow)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xLow && y > yLow && y < yHigh)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xLow && y == yHigh)
                Wall::quadVector[x][y].push_back(13);
            else if(y == yHigh && x > xLow && x < xHigh)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xHigh && y == yHigh)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xHigh && y > yLow && y < yHigh)
                Wall::quadVector[x][y].push_back(13);
            else if(x == xHigh && y == yLow)
                Wall::quadVector[x][y].push_back(13);
            else if(y == yLow && x > xLow && x < xHigh)
                Wall::quadVector[x][y].push_back(13);
            else if( (x > xLow && x < xHigh) && (y > yLow && y < yHigh) )
                Wall::quadVector[x][y].push_back(13);
            else
                Wall::quadVector[x][y].push_back(0);
        }
    }
}

