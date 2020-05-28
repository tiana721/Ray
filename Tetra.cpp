
#include<iostream>
#include"Tetra.h"
#include "functions.h"
//#include <glm.h>
//using namespace::glm;
//#include "glm.h"
//#include "type_vec3.h"
//#include "glm.h"
//using namespace::glm;

void Tetra::print() const{
    if(vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    for(int i = 0; i < 12; i++)
       std::cout << vertex.at(i) <<" "<< std::endl;
    return;
}

void Tetra::set_val(const double num){
    if(vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    vertex.push_back(num);
    return;
}

Point Tetra::get_Center() const {
    if (vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    double x0 = (vertex.at(0) + vertex.at(3) + vertex.at(6) + vertex.at(9)) / 4;
    double y0 = (vertex.at(1) + vertex.at(4) + vertex.at(7) + vertex.at(10)) / 4;
    double z0 = (vertex.at(2) + vertex.at(5) + vertex.at(8) + vertex.at(11)) / 4;
    return Point(x0, y0, z0);
}

std::vector<double> Tetra::get_vert1() const{
    if (vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    vector<double> vect = { vertex.at(0), vertex.at(1) , vertex.at(2) };
    return vect;
}

std::vector<double> Tetra::get_vert2() const {
    if (vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    vector<double> vect = { vertex.at(3), vertex.at(4) , vertex.at(5) };
    return vect;
}

std::vector<double> Tetra::get_vert3() const {
    if (vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    vector<double> vect = { vertex.at(6), vertex.at(7) , vertex.at(8) };
    return vect;
}

std::vector<double> Tetra::get_vert4() const {
    if (vertex.size() != 12)
        throw std::invalid_argument("Error! vertex_Len != 12");
    vector<double> vect = { vertex.at(9), vertex.at(10) , vertex.at(11) };
    return vect;
}

int Tetra::intersect(const Ray& ray, std::vector<double>& point) const
{
    double dist[] = {0, 0, 0, 0}, mindist = 0;
    dist[0] = triangle_intersect(ray, this->get_vert1(), this->get_vert2(), this->get_vert3()); //123
    dist[1] = triangle_intersect(ray, this->get_vert3(), this->get_vert4(), this->get_vert1()); //134
    dist[2] = triangle_intersect(ray, this->get_vert1(), this->get_vert4(), this->get_vert2()); //124
    dist[3] = triangle_intersect(ray, this->get_vert3(), this->get_vert4(), this->get_vert2()); //234
    if ((dist[0] > 0) || (dist[1] > 0) || (dist[2] > 0) || (dist[3] > 0)) {
        for (int i = 0; i < 4; i++) {
            if (!is_equal(dist[i], 0)) {
                mindist = dist[i];
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            if((dist[i] <= mindist)&&(!is_equal(dist[i], 0)))
                mindist = dist[i];
        }
        vector<double> dir = ray.get_dir();
        Normalize("vect", dir);
        point.clear();
        point = { ray.get_dirX() + dir.at(0) * mindist, ray.get_dirY() + dir.at(1) * mindist, ray.get_dirZ() + dir.at(2) * mindist };
        return 1;
    }
    return 0;
}

vector<int> Tetra::getSurfwithPnt(const Ray& ray) const
{
    double dist[] = { 0, 0, 0, 0 }, mindist = 0;
    dist[0] = triangle_intersect(ray, this->get_vert1(), this->get_vert2(), this->get_vert3()); //123
    dist[1] = triangle_intersect(ray, this->get_vert3(), this->get_vert4(), this->get_vert1()); //134
    dist[2] = triangle_intersect(ray, this->get_vert1(), this->get_vert4(), this->get_vert2()); //124
    dist[3] = triangle_intersect(ray, this->get_vert3(), this->get_vert4(), this->get_vert2()); //234
    if ((dist[0] > 0) || (dist[1] > 0) || (dist[2] > 0) || (dist[3] > 0)) {
        for (int i = 0; i < 4; i++) {
            if (!is_equal(dist[i], 0)) {
                mindist = dist[i];
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            if ((dist[i] <= mindist) && (!is_equal(dist[i], 0)))
                mindist = dist[i];
        }
        vector<int> res;
        res.clear();
        if (is_equal(mindist, dist[0])) { res = { 1, 2, 3 }; return res; }
        if (is_equal(mindist, dist[1])) { res = { 1, 3, 4 }; return res; }
        if (is_equal(mindist, dist[2])) { res = { 1, 2, 4 }; return res; }
        if (is_equal(mindist, dist[3])) { res = { 2, 3, 4 }; return res; }
        
        return { 0, 0, 0 };
    }
    return {0, 0, 0};
}

RGB Tetra::get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const
{ 

    double product;
    Ray toLight(inter, Point(light));
    vector<double> vert1 = this->get_vert1(), vert2 = this->get_vert2(), vert3 = this->get_vert3(), vert4 = this->get_vert4();
    vector<double> norm = {0, 0, 0};
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    vector<int> numbers = this->getSurfwithPnt(Ray(cam, inter));
    vector<vector<double>> vertex;
    //cout << numbers.at(0) << numbers.at(1) << numbers.at(2) << endl;
    if (numbers.size() != 3)
        throw std::invalid_argument("Error! numbers.size()!=3 in get_color");
    if ((numbers[0] == 1) || (numbers[1] == 1)|| (numbers[2] == 1)) vertex.push_back(vert1);
    if ((numbers[0] == 2) || (numbers[1] == 2) || (numbers[2] == 2)) vertex.push_back(vert2);
    if ((numbers[0] == 3) || (numbers[1] == 3) || (numbers[2] == 3)) vertex.push_back(vert3);
    if ((numbers[0] == 4) || (numbers[1] == 4) || (numbers[2] == 4)) vertex.push_back(vert4);
    if(vertex.size()!=3)
        throw std::invalid_argument("Error! vertex.size()!=3 in get_color");
    /*s1 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vertex.at(0), vertex.at(1), vertex.at(2), vertex.at(3), \
        vertex.at(4), vertex.at(5), vertex.at(6), vertex.at(7), vertex.at(8));
    s2 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vertex.at(0), vertex.at(1), vertex.at(2), vertex.at(6), \
        vertex.at(7), vertex.at(8), vertex.at(9), vertex.at(10), vertex.at(11));
    s3 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vertex.at(0), vertex.at(1), vertex.at(2), vertex.at(3), \
        vertex.at(4), vertex.at(5), vertex.at(9), vertex.at(10), vertex.at(11));
    s4 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vertex.at(3), vertex.at(4), vertex.at(5), vertex.at(6), \
        vertex.at(7), vertex.at(8), vertex.at(9), vertex.at(10), vertex.at(11));*/
    /*vector<double> vert1 = this->get_vert1(), vert2 = this->get_vert2(), vert3 = this->get_vert3(), vert4 = this->get_vert4();
    s1 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vert1, vert2, vert3);//123
    s2 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vert1, vert3, vert4);//134
    s3 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vert1, vert2, vert4);//124
    s1 = inside_triangle(inter.getX(), inter.getY(), inter.getZ(), vert2, vert3, vert4);//234
    if ((s1 == s2) && (s2 == s3) && (s3 == s4) && (s4 == 0)) {
        cout << s1 << s2 << s3 << s4 << endl;
        throw std::invalid_argument("Error! inter is'n on tetra");
    }
    //123
    if(s1)
    { 
        Ray vect1(Point(this->get_vert1()), Point(this->get_vert2())), vect2(Point(this->get_vert1()), Point(this->get_vert3()));
        norm.clear();
        norm = cross(vect1.get_dir(), vect2.get_dir());
    }
    //134
    if (s2)
    {
        Ray vect1(Point(this->get_vert1()), Point(this->get_vert3())), vect2(Point(this->get_vert1()), Point(this->get_vert4()));
        norm.clear();
        norm = cross(vect1.get_dir(), vect2.get_dir());
    }
    //124
    if (s3)
    {
        Ray vect1(Point(this->get_vert1()), Point(this->get_vert2())), vect2(Point(this->get_vert1()), Point(this->get_vert4()));
        norm.clear();
        norm = cross(vect1.get_dir(), vect2.get_dir());
    }
    //234
    if (s4)
    {
        Ray vect1(Point(this->get_vert2()), Point(this->get_vert3())), vect2(Point(this->get_vert2()), Point(this->get_vert4()));
        norm.clear();
        norm = cross(vect1.get_dir(), vect2.get_dir());
    }*/
    Ray vect1(Point(vertex.at(0)), Point(vertex.at(1))), vect2(Point(vertex.at(0)), Point(vertex.at(2)));
    norm.clear();
    norm = cross(vect1.get_dir(), vect2.get_dir());
    //norm = cross( vect2.get_dir(), vect1.get_dir());
    Normalize("vect", norm);
    Ray normal_ray(norm, inter);
    vector<double> new_pnt = {0, 0, 0};
    int new_inter = 0;
    new_inter = this->intersect(normal_ray, new_pnt);
    if (new_inter) {
        norm.at(0) = -norm.at(0);
        norm.at(1) = -norm.at(1);
        norm.at(2) = -norm.at(2);
    }

    product = (norm.at(0) * toLight.get_dirX() + norm.at(1) * toLight.get_dirY() + norm.at(2) * toLight.get_dirZ());
    if (product < 0)
        return RGB(0, 0, 0);
    unsigned char red, green, blue;
    //cout << product<<endl;
    red = static_cast<int>(this->get_Red() * product);
    green = static_cast<int>(this->get_Green() * product);
    blue = static_cast<int>(this->get_Blue() * product);
    return RGB(red, green, blue);
    //return RGB(255, 255, 255); 

}


// orig и dir задают начало и направление луча. v0, v1, v2 - вершины треугольника.
// ‘ункци€ возвращает рассто€ние от начала луча до точки пересечени€ или 0.
/*double triangle_intersection(const vec3& orig,
    const vec3& dir,
    const vec3& v0,
    const vec3& v1,
    const vec3& v2) {
    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;
    // ¬ычисление вектора нормали к плоскости
    vec3 pvec = cross(dir, e2);
    double det = dot(e1, pvec);

    // Ћуч параллелен плоскости
    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }

    double inv_det = 1 / det;
    vec3 tvec = orig - v0;
    double u = dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }

    vec3 qvec = cross(tvec, e1);
    double v = dot(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    return dot(e2, qvec) * inv_det;
}*/