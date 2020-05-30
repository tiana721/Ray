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

/*std::vector<double> Box::get_vert1() const {
    std::vector<double> res = { maxVert[0], };
}*/

Point Box::get_Center() const {
    return Point((maxVert[0] - minVert[0])/2, (maxVert[1] - minVert[1]) / 2, (maxVert[2] - minVert[2]) / 2);
}

int Box::intersect(const Ray& ray, std::vector<double>& point) const
{
    if (ray.get_pntX() >= minVert[0] && ray.get_pntX() <= maxVert[0] &&
        ray.get_pntY() >= minVert[1] && ray.get_pntY() <= maxVert[1] &&
        ray.get_pntZ() >= minVert[2] && ray.get_pntZ() <= maxVert[2]) {
        //return true;
        //throw std::invalid_argument("Error! cam is in the box");
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

vector<double> Box::min_vert() const {
    vector<double> res = { minVert[0], minVert[1], minVert[2] };
    return res;

}

vector<double> Box::max_vert() const {
    vector<double> res = { maxVert[0], maxVert[1], maxVert[2] };
    return res;

}

RGB Box::get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const {
    
    if (light.size() != 3)
        throw std::invalid_argument("Error! light.size() != 3 in get_ColorOfPoint");
    Ray toLight(inter, Point(light));
    //n = (x-x0)/r, (y-y0)/r, (z-z0)/r
    vector<double> normX = { 1, 0, 0 }, normminX = { -1, 0, 0 }, normY = { 0, 1, 0 }, normminY = { 0, -1, 0 },\
        normZ = {0, 1, 0}, normminZ = { 0, -1, 0 }, norm = normX, vert1, vert2, vert3, vert4, vert5, maxv, minv;
    int product = 0;
    /*norm.push_back((inter.getX() - Center[0]) / Radius);
    norm.push_back((inter.getY() - Center[1]) / Radius);
    norm.push_back((inter.getZ() - Center[2]) / Radius);*/
    //Normalize("vect", norm);
    //scalar product
    vert1 = { maxVert[0],  minVert[1], minVert[2] };
    vert2 = { minVert[0],  minVert[1], maxVert[2] };
    vert3 = { minVert[0],  maxVert[1], maxVert[2] };
    vert4 = { maxVert[0],  maxVert[1], minVert[2] };
    vert5 = { maxVert[0],  minVert[1], maxVert[2] };
    maxv = this->max_vert();
    minv = this->min_vert();
    Ray edge1(minv, vert1), edge2(minv, vert2), edge3(maxv, vert3), edge4(maxv, vert4), edge5(maxv, vert5);
    int new_inter = 0;
    vector<double> new_pnt;

    //Plane Ax + By + Cz + D = 0
    //double A = norm[0], B = norm[1], C = norm[2],\
        //D = -(norm[0] * Center.getX() + norm[1] * Center.getY() + norm[2] * Center.getZ()), Dist = 0, SumOfSq = 0;

    if (is_equal(inter.getX(), minVert[0])) {
        //norm = cross(edge4.get_dir(), edge5.get_dir());
        norm = normX;
        double A = norm[0], B = norm[1], C = norm[2],\
        D = -(norm[0] * inter.getX() + norm[1] * inter.getY() + norm[2] * inter.getZ());
        
        Ray LighttoVert(light, maxv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(0) < minVert[0])
                norm = normminX;

        }
        else if (light.at(0) > minVert[0])// no intersect plane | out light
            norm = normminX;

    }
    if ((is_equal(inter.getX(), maxVert[0]))) {
        norm = normX;
        double A = norm[0], B = norm[1], C = norm[2], \
            D = -(norm[0] * inter.getX() + norm[1] * inter.getY() + norm[2] * inter.getZ());

        Ray LighttoVert(light, minv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(0) < maxVert[0])
                norm = normminX;

        }
        else if (light.at(0) > maxVert[0])// no intersect plane | out light
            norm = normminX;
    }
    if (is_equal(inter.getY(), maxVert[1])) {
        norm = normY;
        Ray LighttoVert(light, minv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(1) < maxVert[1])
                norm = normminY;

        }
        else if (light.at(1) > maxVert[1])// no intersect plane | out light
            norm = normminY;
    }
    if (is_equal(inter.getY(), minVert[1]) ) {
        norm = normY;
        Ray LighttoVert(light, maxv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(1) < minVert[1])
                norm = normminY;

        }
        else if (light.at(1) > minVert[1])// no intersect plane | out light
            norm = normminY;
    }
    if ( is_equal(inter.getZ(), maxVert[2])) {
        norm = normZ;
        Ray LighttoVert(light, minv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(2) < maxVert[2])
                norm = normminZ;

        }
        else if (light.at(2) > maxVert[2])// no intersect plane | out light
            norm = normminZ;
    }
    if (is_equal(inter.getZ(), minVert[2]) ) {
        norm = normZ;
        Ray LighttoVert(light, maxv);
        if (!is_equal(dot(norm, LighttoVert.get_dir()), 0)) {// line intersect plane | to light
            if (light.at(2) < minVert[2])
                norm = normminZ;

        }
        else if (light.at(2) > minVert[2])// no intersect plane | out light
            norm = normminZ;
    }
    /*if (is_equal(inter.getX(), maxVert[0])) {
        norm = normX;
        new_inter = this->intersect(Ray(normX, inter), new_pnt);
        if (new_inter)
            norm = normminX;
        //norm = normX;
    }
    if (is_equal(inter.getX(), minVert[0])) {
        norm = normX;
        //norm = normminX;
    }
    if (is_equal(inter.getY(), maxVert[1]))
        norm = normminY;
        //norm = normY;
    if (is_equal(inter.getY(), minVert[1]))
        norm = normY;
        //norm = normminY;
    if (is_equal(inter.getZ(), maxVert[2]))
        norm = normminZ;
        //norm = normZ;
    if (is_equal(inter.getZ(), minVert[2]))
        norm = normZ;*/
        //norm = normminZ;
    //cout << norm.at(0) << norm.at(1) << endl;
    //cout << toLight.get_dirX() << toLight.get_dirY()<< toLight.get_dirZ() << endl;
    double dot = norm.at(0) * toLight.get_dirX() + norm.at(1) * toLight.get_dirY() + norm.at(2) * toLight.get_dirZ();
    int flag = 0;
    if (!is_equal(dot, 0))
        flag = 1;
    
    //cout << norm.at(0)<< norm.at(1)<< norm.at(2) << endl;
    //cout << product << endl;
    
    //product = static_cast<int>(norm.at(0) * toLight.get_dirX() + norm.at(1) * toLight.get_dirY() + norm.at(2) * toLight.get_dirZ());
    if (dot <= 0) {
        return RGB(0, 0, 0);
    }
    /*for (int i = 0; i < 3; i++)
    {
        if (k < 0.992) color[i] = int(color[i] * k);
        if (k >= 0.992) color[i] = 255;
    }*/
    //abs(dist - r) <= 1e-5
    //if (dot >= 0.992) {
    if ((dot - 0.992) >= 1e-5) {
        return RGB(255, 255, 255);
    }
 
    /*if (flag == 1 && product == 0) {
        dot *= 10;
        product = static_cast<int>(dot);
        //cout << "HERE" <<dot<< endl;
    }*/
    //product = static_cast<int>(dot);
    double red = this->get_Red(), green = this->get_Green(), blue = this->get_Blue();
    red *= dot;
    green *= dot;
    blue *= dot;
    return RGB(static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue));
    /*if (product <= 0)
        return RGB(0, 0, 0);
    return RGB(this->get_Red() * product, this->get_Green() * product, this->get_Blue() * product);*/
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