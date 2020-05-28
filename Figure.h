#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include"Ray.h"
#include"RGB.h"
#include"Point.h"
using namespace std;
class Figure
{
       RGB Color;
       public:
              Figure();
              Figure(const RGB color);
              Figure(const unsigned char red, const unsigned char green, const unsigned char blue);
              unsigned char get_Blue() const;
              unsigned char get_Green() const;
              unsigned char get_Red() const;
              void set_RGB(const RGB color);
              void set_color(const unsigned char red, const unsigned char green, const unsigned char blue);
              virtual void print() const = 0;
              virtual Point get_Center() const = 0;
              //int IsNotInTheArea(const Point Center, const vector<double> &normal, const vector<double> &cam, const double limit, const double alpha, const double screenDist);
              int IsNotInTheArea(const Point Center, const map<string, vector<double>>* params);
              //std::vector<double>
              virtual int intersect(const Ray& ray, std::vector<double>& point) const = 0;
              virtual RGB get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const = 0;
              virtual ~Figure();
              //friend class RGB;
};

#endif // FIGURE_H_INCLUDED
