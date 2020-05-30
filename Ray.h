#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED
#include <iostream>
#include <vector>
#include "Point.h"

class Ray
{
    double point[3], dir[3];
    //std::vector<doub>
    public:
           Ray();
           Ray(const double x0, const double y0, const double z0, const double x1, const double y1, const double z1);
           Ray(const Point& beg, const Point& end);
           Ray(const std::vector<double>& vect, const Point& beg);
           void set_pnt(const double x, const double y, const double z);
           void set_dir(const double x, const double y, const double z);
           void set_dir(const std::vector<double>& vect);
           double get_pntX() const;
           double get_pntY() const;
           double get_pntZ() const;
           double get_dirX() const;
           double get_dirY() const;
           double get_dirZ() const;
           double get_pnti(const int i) const;
           double get_diri(const int i) const;
           std::vector<double> get_dir() const;
           std::vector<double> get_pnt() const;
};

#endif // RAY_H_INCLUDED
