#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>

#include"Figure.h"
#include"RGB.h"
#include"Ray.h"
#include"Point.h"


using namespace std;
#define PI 3.14159265

Figure::Figure()
{
       /*Color.rgbBlue = 0;
       Color.rgbGreen = 0;
       Color.rgbRed = 0;*/
       Color = RGB(0, 0, 0);
}

Figure::Figure(const RGB color) { 
    Color.set_blue(color.get_blue()); 
    Color.set_red(color.get_red());
    Color.set_green(color.get_green());
}

Figure::Figure(const unsigned char red, const unsigned char green, const unsigned char blue)
{
       /*Color.rgbBlue = blue;
       Color.rgbGreen = green;
       Color.rgbRed = red;*/
       Color = RGB(red, green, blue);
}

void Figure::set_RGB(const RGB color) { Color = color; }

Figure::~Figure(){};

unsigned char Figure::get_Blue() const{
    return Color.get_blue();
}

unsigned char Figure::get_Green() const{
    return Color.get_green();
}

unsigned char Figure::get_Red() const{
    return Color.get_red();
}

void Figure::set_color(const unsigned char red, const unsigned char green, const unsigned char blue){
    Color = RGB(red, green, blue);
    return;
}

//int IsNotInTheArea(const Point Center, const vector<double> &normal, const vector<double> &cam, const double limit, const double alpha, const double screenDist)
int Figure::IsNotInTheArea(const Point Center, const map<string, vector<double>>* params)
{
    //Point Camera(cam.at(0), cam.at(1), cam.at(2));

    
    Point Camera(params->find("cam")->second.at(0), params->find("cam")->second.at(1), params->find("cam")->second.at(2));
    //double k = params.find("cam")->second.at(0);
    Ray CamToCent(Camera, Center);
    int AlphaIsRight = 0, DistIsRight = 0;
    //Get parameters 
    double Nlen, Rlen, Cos = 0, alpha = params->find("alpha")->second.at(0),\
        norm[3] = { params->find("normal")->second.at(0) , params->find("normal")->second.at(1) , params->find("normal")->second.at(2)},\
        screenDist = params->find("screen")->second.at(0), limit = params->find("limit")->second.at(0);
    //Calculate
    Rlen = pow((pow(CamToCent.get_dirX(), 2) + pow(CamToCent.get_dirY(), 2) + pow(CamToCent.get_dirZ(), 2)), 0.5);
    Nlen = pow((pow(norm[0], 2) + pow(norm[1], 2) + pow(norm[2], 2)), 0.5);
    Cos = CamToCent.get_dirX() * norm[0] + CamToCent.get_dirY() * norm[1] + CamToCent.get_dirZ() * norm[2];
    if(Nlen == 0) throw invalid_argument("Error! Length or normal = 0");
    Cos /= Nlen * Rlen;
    if ((acos(Cos) * 180 / PI) <= alpha / 2) AlphaIsRight = 1;
    cout << "angle: "<<acos(Cos) * 180 / PI << endl;
    //Plane Ax + By + Cz + D = 0
    double A = norm[0], B = norm[1], C = norm[2],\
        D = -(norm[0] * Center.getX() + norm[1] * Center.getY() + norm[2] * Center.getZ()), Dist = 0, SumOfSq = 0;
    Dist = abs(A * Camera.getX() + B * Camera.getY() + C * Camera.getZ() + D);
    SumOfSq = pow((A * A + B * B + C * C), 1 / 2);
    if (SumOfSq == 0) throw invalid_argument("Error! A * A + B * B + C * C = 0 in Ax + By + Cz + D = 0");
    Dist /= SumOfSq;
    if (Dist < screenDist + limit) DistIsRight = 1;
    cout << "Area "<<DistIsRight <<" "<< AlphaIsRight << endl;
    if((DistIsRight + AlphaIsRight) != 2)
        return 1;
    return 0;
    
}