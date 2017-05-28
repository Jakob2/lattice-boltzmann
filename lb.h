#ifndef LB_H
#define LB_H

#include "global.h"
#include "wall.h"

class Lb : public Wall
{
public:
    Lb();

    void initialize();
    void setDensity(Lb &point);
    void setSpeed(Lb &point, int x);
    void setEquilibrium(Lb &point);
    void setRelax(Lb &point);
    void stream(vector<vector<vector<Lb>>> &points);


    vector<vector<vector<Lb>>> points;
    void setPoints(int x, int y, Lb &point);
    Lb &getPoints(int x, int y);

    vector<double> initF = {0.13333, 0.13333, 0.13333, 0.13333, 0.13333, 0.13333, 0.13333, 0.13333, 0.13333};
    //vector<vector<double>> initC = {{0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {LR_SPEED,0.0}, {0.0,0.0}, {0.0,0.0}};
    vector<vector<double>> p ={{0.0,0.0}, {-1.0,-1.0}, {-1.0,0.0}, {-1.0,1.0}, {0.0,1.0}, {1.0,1.0}, {1.0,0.0}, {1.0,-1.0}, {0.0,-1.0}};
    vector<double> w = {0.44444, 0.02777, 0.11111, 0.02777, 0.11111, 0.02777, 0.11111, 0.02777, 0.11111};
    const double cs = 1.73205;
    const double tau = 1.0;
    vector<vector<int>> q = {{0,0}, {1,5}, {2,6}, {3,7}, {4,8}, {5,1}, {6,2}, {7,3}, {8,4}};

    vector<double> f;
    vector<double> tf;
    vector<vector<double>> c;

    double density;
    vector<double> speed;
    vector<double> equi;

private:
    void redistribute(Lb &middle, Lb &side, int index);
    void bounceBack(Lb &point, int oldpos, int newpos);
    void visual(float x, float y, float z, double r, double g, double b);
    double scalarproduct(double aZero, double aOne, double bZero, double bOne);

};

#endif // LB_H
