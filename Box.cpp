#include<iostream>
#include<cmath>
#include<limits>
#include"Box.h"
#include "functions.h"

using namespace std;

void Box::print() const{
    cout <<"minVert "<<minVert[0]<<" "<<minVert[1]<<" "<<minVert[2]<<" "<<endl;
    cout <<"maxVert "<<maxVert[0]<<" "<<maxVert[1]<<" "<<maxVert[2]<<" "<<endl;
    return;
}

void Box::set_minV(const double x, const double y, const double z){
    minVert[0] = x;
    minVert[1] = y;
    minVert[2] = z;
    return;
}

void Box::set_maxV(const double x, const double y, const double z){
    maxVert[0] = x;
    maxVert[1] = y;
    maxVert[2] = z;
    return;
}

Point Box::get_Center() const {
    return Point((maxVert[0] - minVert[0])/2, (maxVert[1] - minVert[1]) / 2, (maxVert[2] - minVert[2]) / 2);
}

int Box::intersect(const Ray& ray, std::vector<double>& point) const
{
    if (ray.get_pntX() >= minVert[0] && ray.get_pntX() <= maxVert[0] &&
        ray.get_pntY() >= minVert[1] && ray.get_pntY() <= maxVert[1] &&
        ray.get_pntZ() >= minVert[2] && ray.get_pntZ() <= maxVert[2]) {
        //return true;
        throw std::invalid_argument("Error! cam is in the box");
        return 1;
    }

    // ray parameter
    double t_near = numeric_limits<double>::min(),
        t_far = numeric_limits<double>::max();
    double t1, t2;

    // directions loop
    for (int i = 0; i < 3; i++) {
        if (abs(ray.get_diri(i)) >= std::numeric_limits<double>::epsilon()) {
            t1 = (minVert[i] - ray.get_pnti(i)) / ray.get_diri(i);
            t2 = (maxVert[i] - ray.get_pnti(i)) / ray.get_diri(i);

            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > t_near)
                t_near = t1;
            if (t2 < t_far)
                t_far = t2;

            if (t_near > t_far)
                return 0;
                //return false;
            if (t_far < 0.0)
                return 0;
                //return false;
        } // if
        else {
            if (ray.get_pnti(i) < minVert[i] || ray.get_pnti(i) > maxVert[i])
                return 0;
                //return false;
        }
    } // for

    //return (t_near <= t_far && t_far >= 0);
    if (t_near <= t_far && t_far >= 0) {
        point.clear();
        point = {ray.get_pntX() + ray.get_dirX() * t_near, ray.get_pntY() + ray.get_dirY() * t_near ,\
            ray.get_pntZ() + ray.get_dirZ() * t_near };
        return 1;
    }
    return 0;
}

RGB Box::get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const {
    
    if (light.size() != 3)
        throw std::invalid_argument("Error! light.size() != 3 in get_ColorOfPoint");
    Ray toLight(inter, Point(light));
    //n = (x-x0)/r, (y-y0)/r, (z-z0)/r
    vector<double> normX = { 1, 0, 0 }, normminX = { -1, 0, 0 }, normY = { 0, 1, 0 }, normminY = { 0, -1, 0 },\
        normZ = {0, 1, 0}, normminZ = { 0, -1, 0 }, norm = normX;
    int product = 0;
    /*norm.push_back((inter.getX() - Center[0]) / Radius);
    norm.push_back((inter.getY() - Center[1]) / Radius);
    norm.push_back((inter.getZ() - Center[2]) / Radius);*/
    //Normalize("vect", norm);
    //scalar product

    /*if( is_equal(inter.getX(), minVert[0]) || is_equal(inter.getX(), maxVert[0]))
        norm = normX;
    if (is_equal(inter.getY(), minVert[1]) || is_equal(inter.getY(), maxVert[1]))
        norm = normY;
    if (is_equal(inter.getZ(), minVert[2]) || is_equal(inter.getZ(), maxVert[2]))
        norm = normZ;
    */
    if(is_equal(inter.getX(), maxVert[0]))
        norm = normX;
    if (is_equal(inter.getX(), minVert[0]))
        norm = normminX;
    if (is_equal(inter.getY(), maxVert[1]))
        norm = normY;
    if (is_equal(inter.getY(), minVert[1]))
        norm = normminY;
    if (is_equal(inter.getZ(), maxVert[2]))
        norm = normZ;
    if (is_equal(inter.getZ(), minVert[2]))
        norm = normminZ;

    product = static_cast<int>(norm.at(0) * toLight.get_dirX() + norm.at(1) * toLight.get_dirY() + norm.at(2) * toLight.get_dirZ());
    //cout << norm.at(0)<< norm.at(1)<< norm.at(2) << endl;
    if (product < 0)
        return RGB(0, 0, 0);
    return RGB(this->get_Red() * product, this->get_Green() * product, this->get_Blue() * product);
    //return RGB(255, 255, 255); 
}

//bool RayBoxIntersection(float3 ray_pos, float3 inv_dir, float3 boxMin, float3 boxMax, float& tmin, float& tmax)
/*int Box::intersect(const Ray* ray, std::vector<double>& point)
{

    float lo = inv_dir.x * (boxMin.x - ray_pos.x);

    float hi = inv_dir.x * (boxMax.x - ray_pos.x);

    tmin = min(lo, hi);

    tmax = max(lo, hi);



    float lo1 = inv_dir.y * (boxMin.y - ray_pos.y);

    float hi1 = inv_dir.y * (boxMax.y - ray_pos.y);

    tmin = max(tmin, min(lo1, hi1));

    tmax = min(tmax, max(lo1, hi1));



    float lo2 = inv_dir.z * (boxMin.z - ray_pos.z);

    float hi2 = inv_dir.z * (boxMax.z - ray_pos.z);

    tmin = max(tmin, min(lo2, hi2));

    tmax = min(tmax, max(lo2, hi2));



    if (tmin <= tmax) && (tmax > 0.f)
        return 1;
    return 0;

}*/