
#include<iostream>
#include <cmath>
#include"Ray.h"
Ray::Ray()
{
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
}

void Ray::set_pnt(const double x, const double y, const double z)
{
    point[0] = x;
    point[1] = y;
    point[2] = z;
    return;
}

void Ray::set_dir(const double x, const double y, const double z)
{
    double length = pow((x * x + y * y + z * z), 0.5);
    if(length == 0)
        throw std::invalid_argument("Error! ||ray.dir|| == 0");
    dir[0] = x / length;
    dir[1] = y / length;
    dir[2] = z / length;
    return;
}

double Ray::get_pntX() const
{
    return point[0];
}

double Ray::get_pntY() const
{
    return point[1];
}

double Ray::get_pntZ() const
{
    return point[2];
}

double Ray::get_dirX() const
{
    return dir[0];
}

double Ray::get_dirY() const
{
    return dir[1];
}

double Ray::get_dirZ() const
{
    return dir[2];
}

Ray::Ray(const double x0, const double y0, const double z0, const double x1, const double y1, const double z1)
{
    //if ( pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2) == 0)
        //throw std::invalid_argument("Error! ||ray.dir|| == 0 in constructor");
    double length = pow((pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2)), 0.5);
    if (length == 0)
        throw std::invalid_argument("Error! ||ray.dir|| == 0 in constructor");
    point[0] = x0;
    point[1] = y0;
    point[2] = z0;
    dir[0] = (x1 - x0) / length;
    dir[1] = (y1 - y0) / length;
    dir[2] = (z1 - z0) / length;
}

Ray::Ray(const Point& beg, const Point& end)
{
    double x0 = beg.getX(), y0 = beg.getY(), z0 = beg.getZ(), x1 = end.getX(), y1 = end.getY(), z1 = end.getZ();
    //if (pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2) == 0)
       // throw std::invalid_argument("Error! ||ray.dir|| == 0 in constructor");
    double length = pow((pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2)), 0.5);
    if (length == 0)
        throw std::invalid_argument("Error! ||ray.dir|| == 0 in constructor");
    point[0] = x0;
    point[1] = y0;
    point[2] = z0;
    dir[0] = (x1 - x0) / length;
    dir[1] = (y1 - y0) / length;
    dir[2] = (z1 - z0) / length;
}

void Ray::set_dir(const std::vector<double>& vect)
{
    if(vect.size() != 3)
        throw std::invalid_argument("Error! vect.size() != 3 in Ray.set");
    double length = pow((pow(vect.at(0), 2) + pow(vect.at(1), 2) + pow(vect.at(2), 2)), 0.5);
    if (length == 0)
        throw std::invalid_argument("Error! ||ray.dir|| == 0 in set");
    dir[0] = vect.at(0) / length;
    dir[1] = vect.at(1) / length;
    dir[2] = vect.at(2) / length;
}

Ray::Ray(const std::vector<double>& vect, const Point& beg)
{
    if (vect.size() != 3)
        throw std::invalid_argument("Error! vect.size() != 3 in Ray");
    double length = pow((pow(vect.at(0), 2) + pow(vect.at(1), 2) + pow(vect.at(2), 2)), 0.5);
    //if (length == 0)
        //throw std::invalid_argument("Error! ||ray.dir|| == 0 in constructor");
    dir[0] = vect.at(0) / length;
    dir[1] = vect.at(1) / length;
    dir[2] = vect.at(2) / length;
    point[0] = beg.getX();
    point[1] = beg.getY();
    point[2] = beg.getZ();
}

double Ray::get_pnti(const int i) const
{
    if((i >= 3) || (i < 0))
        throw std::invalid_argument("Error! Index out of range");
    return point[i];
}

double Ray::get_diri(const int i) const {
    if ((i >= 3) || (i < 0))
        throw std::invalid_argument("Error! Index out of range");
    return dir[i];
}

std::vector<double> Ray::get_dir() const
{
    std::vector<double> vect = {dir[0], dir[1], dir[2]};
    return vect;
}

std::vector<double> Ray::get_pnt() const
{
    std::vector<double> vect = { point[0], point[1], point[2] };
    return vect;
}