#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include <vector>
#include "Figure.h"
#include "Ray.h"
#include "Point.h"

class Sphere : public Figure{
    double Center[3];
    double Radius;
    public:
           Sphere() : Figure(){
               Center[0] = 0;
               Center[1] = 0;
               Center[2] = 0;
               Radius = 0;
           };
           Sphere(const RGB color) : Figure(color) {
               Center[0] = 0;
               Center[1] = 0;
               Center[2] = 0;
               Radius = 0;
           };
           Sphere(const RGB color, const std::vector<double>& data) : Figure(color) {
               cout << "HERE" << endl;
               if (data.size() != 4) {
                   Center[0] = 0;
                   Center[1] = 0;
                   Center[2] = 0;
                   Radius = 0;
                   throw std::invalid_argument("Error! Wrong data (Sphere)");
               }
               //for (int i = 0; i < 3; i++) { Center[i] = data.at(i); }
               Center[0] = data.at(0);
               Center[1] = data.at(1);
               Center[2] = data.at(2);
               Radius = data.at(3);
           };
           Sphere(const double x, const double y, const double z,\
                const double R, const unsigned char red, const unsigned char green, const unsigned char blue)\
                : Figure(red, green, blue)
           {
               if(R == 0)
                   throw std::invalid_argument("Error! Radius = 0");
               Center[0] = x;
               Center[1] = y;
               Center[2] = z;
               Radius = R;
           };
           void set_cent(const double x, const double y, const double z);
           void set_rad(const double rad);
           double get_CentX() const;
           double get_CentY() const;
           double get_CentZ() const;
           double get_Rad() const;
           void print() const;
           Point get_Center() const;
           int intersect(const Ray& ray, std::vector<double>& point) const;
           RGB get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const;
           ~Sphere(){};
};

#endif // SPHERE_H_INCLUDED
