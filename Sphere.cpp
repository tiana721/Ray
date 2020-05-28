#include<iostream>
#include <cmath>
#include <vector>
#include "Sphere.h"
#include "Ray.h"
#include "Point.h"
//#include <cstdlib>
#include "functions.h"

using namespace std;
/*Ball::Ball(){
    Center[0] = 0;
    Center[1] = 0;
    Center[2] = 0;
    Radius = 0;
}*/

/*Ball::Ball(const double x, const double y, const double z, const double R){
    Center[0] = x;
    Center[1] = y;
    Center[2] = z;
    Radius = R;
}*/

double Sphere::get_CentX() const{
    return Center[0];
}

double Sphere::get_CentY() const{
    return Center[1];
}

double Sphere::get_CentZ() const{
    return Center[2];
}

double Sphere::get_Rad() const{
    return Radius;
}

void Sphere::print() const
{
    cout<<"Sphere "<<Center[0]<<" "<<Center[1]<<" "<<Center[2]<<" R = "<<Radius<<endl;
  
    return;
}

void Sphere::set_cent(const double x, const double y, const double z){
    Center[0] = x;
    Center[1] = y;
    Center[2] = z;
    return;
}

void Sphere::set_rad(const double rad){
    Radius = rad;
}

Point Sphere::get_Center() const { return Point(Center[0], Center[1], Center[2]); }


int Sphere::intersect(const Ray& ray, std::vector<double>& point) const
{
    //a == 1; // because rdir must be normalized
    Point ray_pos(ray.get_pntX(), ray.get_pntY(), ray.get_pntZ()), spos(Center[0], Center[1], Center[2]);
    //float3 k = ray_pos - spos;
    Ray CentToBeg(spos, ray_pos);
    vector<double> ray_dir, rvect; // rvect = k
    /*rvect.push_back(CentToBeg.get_dirX());
    rvect.push_back(CentToBeg.get_dirY());
    rvect.push_back(CentToBeg.get_dirZ());*/
    rvect.push_back(ray_pos.getX() - spos.getX());
    rvect.push_back(ray_pos.getY() - spos.getY());
    rvect.push_back(ray_pos.getZ() - spos.getZ());
    ray_dir.push_back(ray.get_dirX());
    ray_dir.push_back(ray.get_dirY());
    ray_dir.push_back(ray.get_dirZ());
    //a=1
    double b = 2 * dot(rvect, ray_dir);
    double c = dot(rvect, rvect) - Radius * Radius;
    double d = b * b - 4 * c;
    //A = 1; B = 2 * Dot(P0 - C, Dir); C = Length ^ 2(P0 - C) - R ^ 2;
    //Discr = B * B - 4 * A * C
    /*cout << "ray_dir= " << ray_dir.at(0)<< ray_dir.at(1)<< ray_dir.at(2) << endl;
    cout << "rvect= " << rvect.at(0) << rvect.at(1) << rvect.at(2) << endl;*/
    //cout << "c= " << c << "b= " << b <<"d= " << d <<endl;
    //cout << "b= " << b << endl;
    //cout << "d= " << d << endl;
    if (d >= 0)
    {
        double sqrtd = pow(d, 0.5);

        // t, a == 1
        double t1 = (-b + sqrtd) / 2;

        double t2 = (-b - sqrtd) / 2;

        double min_t = min(t1, t2);

        double max_t = max(t1, t2);

        double tResult = (min_t >= 0) ? min_t : max_t;
        if (tResult < 0)
            return 0;
        //double tResult = t;
        //cout << "t= " << t << endl;
        //if (t > 0) return 1;
        //else return 0;
        //return (t > 0);
        point.clear();
        point = { ray.get_pntX() + ray.get_dirX() * tResult, ray.get_pntY() + ray.get_dirY() * tResult ,\
            ray.get_pntZ() + ray.get_dirZ() * tResult };
        return 1;
    }
    /*else if (d == 0)
    {
        double t = (-b ) / 2;
        if (t < 0)
            return 0;
        return 1;
    }*/
    return 0;
}

/*int Sphere::intersect(const Ray* ray, std::vector<double>& point)
{
    
    double t0 = (Center[0] - ray->get_pntX())*ray->get_dirX() + (Center[1] - ray->get_pntY()) * ray->get_dirY() + (Center[2] - ray->get_pntZ()) * ray->get_dirZ();     //t0=OC*l
    double d_in2 = (Center[0] - ray->get_pntX()) * (Center[0] - ray->get_pntX()) + (Center[1] - ray->get_pntY()) * (Center[1] - ray->get_pntY()) + (Center[2] - ray->get_pntZ()) * (Center[2] - ray->get_pntZ()) - (t0 * t0);
    
    if (Radius * Radius - d_in2 < 0)
        return 0;*/
    /*double param = t0 - sqrt(Radius * Radius - d_in2);
    point.push_back( ray->get_pntX() + param * ray->get_dirX());
    point.push_back(ray->get_pntY() + param * ray->get_dirY());
    point.push_back(ray->get_pntZ() + param * ray->get_dirZ());*/
    //return 1;

//}

RGB Sphere::get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const
{
    Ray toLight(inter, Point(light));
    //n = (x-x0)/r, (y-y0)/r, (z-z0)/r
    vector<double> norm;
    double product = 0;
    norm.push_back((inter.getX() - Center[0]) / Radius);
    norm.push_back((inter.getY() - Center[1]) / Radius);
    norm.push_back((inter.getZ() - Center[2]) / Radius);
    Normalize("vect", norm);
    //scalar product
    //cout << norm[0] << norm[1]<< norm[2] << endl;
    product = (norm.at(0) * toLight.get_dirX() + norm.at(1) * toLight.get_dirY() + norm.at(2) * toLight.get_dirZ());
    
    if (product < 0)
        return RGB(0, 0, 0);
    unsigned char red, green, blue;
    red = static_cast<int>(this->get_Red() * product);
    green = static_cast<int>(this->get_Green() * product);
    blue = static_cast<int>(this->get_Blue() * product);
    return RGB(red, green, blue);
    //return RGB(0, 0, 0);
}