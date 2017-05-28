#include "lb.h"

Lb::Lb(){

}

double Lb::scalarproduct(double aZero, double aOne, double bZero, double bOne)
{
    return (aZero*bZero)+(aOne*bOne);
}

void Lb::setPoints(int x, int y, Lb &point){
    this->points.resize(X_RANGE);
    this->points[x].resize(Y_RANGE);
    this->points[x][y].push_back(point);
}

Lb &Lb::getPoints(int x, int y){
    return this->points[x][y][0];
}

void Lb::initialize(){
    vector<vector<double>> initC = {{0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {0.0,0.0}, {LR_SPEED,0.0}, {0.0,0.0}, {0.0,0.0}};
    this->points.clear();
    this->points.resize(X_RANGE);
    for(int x=0; x<X_RANGE; x++){
        this->points[x].resize(Y_RANGE);
        for(int y=0; y<Y_RANGE; y++){
            Lb point;
            point.f.resize(Q);
            point.tf.resize(Q);
            point.c.resize(Q);
            for(int i=0; i<Q; i++){
                point.c[i].resize(2);
            }

            if(Wall::quadVector[x][y][0] == 13 || y==0 || y==Y_RANGE-1){
                for(int i=0; i<Q; i++){
                    point.f[i] = 0;
                    point.tf[i] = 0;
                    point.c[i][0] = 0;
                    point.c[i][1] = 0;
                }
            }else if(Wall::quadVector[x][y][0] != 13){
                for(int i=0; i<Q; i++){
                    point.f[i] = initF[i];
                    point.tf[i] = initF[i];
                    point.c[i][0] = initC[i][0];
                    point.c[i][1] = initC[i][1];
                }
            }
            this->setPoints(x, y, point);
        }
    }
}

void Lb::setDensity(Lb &point)
{
   double rho = 0.0;
    if(point.f[6]){
        for(int i=0; i<Q; i++){
            if(STEP)
                rho += point.f[i];
            else if(!STEP)
                rho += point.tf[i];
        }
    }
    point.density = rho;
}

void Lb::setSpeed(Lb &point, int x){
    double zero = 0.0;
    double one = 0.0;

    if(point.f[6]){
        for(int i=0; i<Q; i++){
            if(STEP){
                zero += (point.f[i] * point.c[i][0] * point.p[i][0]);
                one += (point.f[i] * point.c[i][1] * point.p[i][1]);
            }else if(!STEP){
                zero += (point.tf[i] * point.c[i][0] * point.p[i][0]);
                one += (point.tf[i] * point.c[i][1] * point.p[i][1]);
            }
        }
        zero = zero / point.density;
        one = one / point.density;
    }
    point.speed.resize(2);
    point.speed[0] = zero;
    point.speed[1] = one;

    if(x==1){
        point.speed[0] = LR_SPEED;
        point.speed[1] = 0.0;
    }
}

void Lb::setEquilibrium(Lb &point)
{
    vector<double> c = {0.0, 0.0};
    vector<double> s = {0.0, 0.0};
    double res = 0.0;
    point.equi.resize(Q);

    if(point.f[6])
    {
        for(int i=0; i<Q; i++)
        {
            c[0] = point.c[i][0];
            c[1] = point.c[i][1];
            s[0] = point.speed[0];
            s[1] = point.speed[1];

            res = point.w[i]*point.density*( 1.0+ (point.scalarproduct(c[0], c[1], s[0], s[1]) / pow(point.cs, 2) ) +
                                                    ( pow( (point.scalarproduct(c[0], c[1], s[0], s[1])), 2) / (2*pow(point.cs, 4)) ) -
                                                    ( (point.scalarproduct(s[0], s[1], s[0], s[1])) / (2*pow(point.cs, 2)) )
                                                );
            point.equi[i] = res;
        }
    }
}

void Lb::setRelax(Lb &point)
{
    double res = 0.0;

    if(point.f[6]){
        for(int i=0; i<Q; i++){
            if(STEP)
                res = point.f[i] - ( pow(point.tau,-1) * (point.f[i] - point.equi[i]) );
            else if(!STEP)
                res =  point.tf[i] - ( pow(point.tau,-1) * (point.tf[i] - point.equi[i]) );
        point.f[i] = res;
        point.tf[i] = res;
        }
    }
}

void Lb::bounceBack(Lb &point, int oldpos, int newpos){
    if(STEP)
        point.tf[newpos] = point.f[oldpos]*(-1);
    else if(!STEP)
        point.f[newpos] = point.tf[oldpos]*(-1);
}

void Lb::redistribute(Lb &middle, Lb &side, int index){
    if(STEP)
        side.tf[index] = middle.f[index];
    else if(!STEP)
        side.f[index] = middle.tf[index];
}

void Lb::stream(vector<vector<vector<Lb>>> &points){

    for(int x=1; x<X_RANGE-1; x++){
        float xf = x;
        for(int  y=1; y<Y_RANGE-1; y++){
            float yf = y;
            if(Wall::quadVector[x][y][0] == 0){
                for(int i=0; i<Q; i++){
                    int ex = points[x][y][0].p[i][0];
                    int ey = points[x][y][0].p[i][1];
                    int oldpos = points[x][y][0].q[i][0];
                    int newpos = points[x][y][0].q[i][1];

                    if(Wall::quadVector[x+ex][y+ey][0] > 0)
                        this->bounceBack(points[x][y][0], oldpos, newpos);
                    else
                        this->redistribute(points[x][y][0], points[x+ex][y+ey][0], i);
                }
                //this->visual(xf/10, points[x][y][0].c[6][0], yf/10, 0,0,points[x][y][0].c[6][0]);
                if(VISUAL) this->visual(xf/10, points[x][y][0].density/10, yf/10, 0,0,points[x][y][0].density);
                if(!VISUAL) this->visual(xf/10, points[x][y][0].speed[0], yf/10, 0,0,points[x][y][0].speed[0]);
                //this->visual(xf/10, 0, yf/10, 0,0,points[x][y][0].speed[0]);
            }
            else{
                this->visual(xf/10, 0, yf/10, 0,1,0);
            }
        }
    }
}

void Lb::visual(float x, float y, float z, double r, double g, double b){
    glPushMatrix();
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex3f(0.05+x, y, -0.05+z);
        glVertex3f(0.05+x, y, 0.05+z);
        glVertex3f(-0.05+x, y, 0.05+z);
        glVertex3f(-0.05+x, y, -0.05+z);
    glEnd();
    glPopMatrix();
}
