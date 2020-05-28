#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <limits>
#include <cmath>
#include <chrono>
#include <omp.h>
#include "Figure.h"
#include "functions.h"
#include "Sphere.h"
#include "Box.h"
#include "Tetra.h"
#include "Ray.h"
#include "CImg.h"
using namespace std;
#define PI 3.14159265  
#define EPS 1e-10
void Check_lenParam(const string& Type, const size_t size)
{
    if ((Type == "cam") && (size != 3)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in cam");
    }
    else if ((Type == "normal") && (size != 3)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in normal");
    }
    else if ((Type == "up") && (size != 3)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in up");
    }
    else if ((Type == "light") && (size != 3)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in light");
    }
    else if ((Type == "screen") && (size != 1)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in screen");
    }
    else if ((Type == "limit") && (size != 1)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in limit");
    }
    else if ((Type == "alpha") && (size != 1)) {
        throw std::invalid_argument ("Error! Wrong data: incorrect length in alpha");
    }
    return;
}

void Check_CntParams(const map<string, vector<double>>* params)
{
    //if(params->find("cam")->)
    if (params->count("cam") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of cam");
    if (params->count("normal") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of normal");
    if (params->count("up") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of up");
    if (params->count("screen") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of screen");
    if (params->count("limit") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of limit");
    if (params->count("alpha") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of alpha");
    if (params->count("light") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of light");
    if (params->size() != 7) 
        throw std::invalid_argument("Error! There are not all parameters");
    return;
}

void Check_Screen(const map<string, int>* screen)
{
    if(screen->size() != 2)
        throw std::invalid_argument("Error! Wrong incorrect count in screen");
    if (screen->count("width") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of width");
    if (screen->count("height") != 1)
        throw std::invalid_argument("Error! Wrong incorrect count of height");
    return;
}

double max(const double a, const double b)
{
    if (a >= b) return a;
    /*if((a - b) > std::numeric_limits<double>::epsilon())
        return a;*/
    else return b;
}

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

double min(const double a, const double b)
{
    if (a <= b) return a;
    /*if ((a - b) < std::numeric_limits<double>::epsilon())
        return a;*/
    else return b;
}



double triangle_square(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return pow((p * (p - a) * (p - b) * (p - c)), 0.5);
}

int inside_triangle(double P_x, double P_y, double P_z, vector<double>& A, vector<double>& B, vector<double>& C){
    //double A_x, double A_y, double A_z, double B_x, double B_y, double B_z, double C_x, double C_y, double C_z) {
    if((A.size()!= 3) || (B.size() != 3) || (C.size() != 3))
        throw std::invalid_argument("Error! vect.size != 3");
    double A_x = A.at(0), A_y = A.at(1), A_z = A.at(2);
    double B_x = B.at(0), B_y = B.at(1), B_z = B.at(2);
    double C_x = C.at(0), C_y = C.at(1), C_z = C.at(2);
    int inside = 0;
    double AB = pow(((A_x - B_x) * (A_x - B_x) + (A_y - B_y) * (A_y - B_y) + (A_z - B_z) * (A_z - B_z)), 0.5);
    double BC = pow(((B_x - C_x) * (B_x - C_x) + (B_y - C_y) * (B_y - C_y) + (B_z - C_z) * (B_z - C_z)), 0.5);
    double CA = pow(((A_x - C_x) * (A_x - C_x) + (A_y - C_y) * (A_y - C_y) + (A_z - C_z) * (A_z - C_z)), 0.5);
    double AP = pow(((P_x - A_x) * (P_x - A_x) + (P_y - A_y) * (P_y - A_y) + (P_z - A_z) * (P_z - A_z)), 0.5);
    double BP = pow(((P_x - B_x) * (P_x - B_x) + (P_y - B_y) * (P_y - B_y) + (P_z - B_z) * (P_z - B_z)), 0.5);
    double CP = pow(((P_x - C_x) * (P_x - C_x) + (P_y - C_y) * (P_y - C_y) + (P_z - C_z) * (P_z - C_z)), 0.5);
    double diff = (triangle_square(AP, BP, AB) + triangle_square(AP, CP, CA) + triangle_square(BP, CP, BC)) - triangle_square(AB, BC, CA);
    cout << fabs(diff) << endl;
    if (fabs(diff) < EPS) inside = 1;
    return inside;
}

void Normalize(const string& Type, vector<double>& vect)
{
    if ((Type != "normal") && (Type != "up") && (Type != "vect"))
        return;
    if (vect.size() != 3)
        throw std::invalid_argument("Error! vect.size != 3");
    double length = pow((vect.at(0) * vect.at(0) + vect.at(1) * vect.at(1) + vect.at(2) * vect.at(2)), 0.5);
    //if(length == 0)
        //throw std::invalid_argument("Error! Module of vect = 0");
    if (length == 0)
        return;
    vect.at(0) /= length;
    vect.at(1) /= length;
    vect.at(2) /= length;
    return;
}

//double triangle_intersect(const vector<double>& orig, const vector<double>& dir, const vector<double>& v0,
//    const vector<double>& v1, const vector<double>& v2)
double triangle_intersect(const Ray& ray, const vector<double>& v0, \
    const vector<double>& v1, const vector<double>& v2)
{
    //vec3 e1 = v1 - v0;
    //vec3 e2 = v2 - v0;
    vector<double> e1 = { v1.at(0) - v0.at(0), v1.at(1) - v0.at(1), v1.at(2) - v0.at(2) }, \
        e2 = { v2.at(0) - v0.at(0), v2.at(1) - v0.at(1), v2.at(2) - v0.at(2) };
    // 
    //vec3 pvec = cross(dir, e2);
    vector<double> pvec = cross(ray.get_dir(), e2);
    double det = dot(e1, pvec);
    
    // 
    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }
    if (det <= 0 && det >= 0) {
        return 0;
    }
    double inv_det = 1 / det;
    //vec3 tvec = orig - v0;
    vector<double> tvec = {ray.get_pntX() - v0.at(0), ray.get_pntY() - v0.at(1), ray.get_pntZ() - v0.at(2) };
    double u = dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }
    //vec3 qvec = cross(tvec, e1);
    vector<double> qvec = cross(tvec, e1);
    double v = dot(ray.get_dir(), qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    return dot(e2, qvec) * inv_det;
    //return 0;
}

int TakeTheNearest(const vector< Figure* >* figrs, const Point* cam)
{
    double min_dist = get_dist(cam, &(figrs->at(0)->get_Center())), cur_dist = 0;
    int min_ind = 0, len = figrs->size();
    for (int i = 1; i < len; i++) {
        cur_dist = get_dist(cam, &(figrs->at(i)->get_Center()));
        if (cur_dist <= min_dist) {
            min_dist = cur_dist;
            min_ind = i;
        }
    }
    return min_ind;
}

vector<double> cross(const vector<double>& a, const vector<double>& b)
{
    vector<double> result;
    if ((a.size() != 3) || (b.size() != 3))
        throw std::invalid_argument("Error! vect.size != 3");
    result.push_back(a.at(1) * b.at(2) - a.at(2) * b.at(1));
    result.push_back(a.at(2) * b.at(0) - a.at(0) * b.at(2));
    result.push_back(a.at(0) * b.at(1) - a.at(1) * b.at(0));
    //cout << a.at(0) << a.at(1) << a.at(2) << endl; //up norm
    //cout << b.at(0) << b.at(1) << b.at(2) << endl;
    //cout << result.at(0) << result.at(1) << result.at(2) << endl;
    //if (result.at(0) * result.at(0) + result.at(1) * result.at(1) + result.at(2) * result.at(2) == 0)
        //throw std::invalid_argument("Error! cross = 0");
        //cout << "Warning! cross = 0" << endl;
    return result;
}

double dot(const vector<double>& a, const vector<double>& b)
{
    double res = 0;
    if ((a.size() != 3) || (b.size() != 3))
        throw std::invalid_argument("Error! vect.size != 3");
    res = a.at(0) * b.at(0) + a.at(1) * b.at(1) + a.at(2) * b.at(2);
    //if (result.at(0) * result.at(0) + result.at(1) * result.at(1) + result.at(2) * result.at(2) == 0)
      //  cout << "Warning! cross = 0" << endl;
    return res;
}

double get_dist(const Point* pnt1, const Point* pnt2)
{
    double x0 = pnt1->getX(), y0 = pnt1->getY(), z0 = pnt1->getZ(), \
        x1 = pnt2->getX(), y1 = pnt2->getY(), z1 = pnt2->getZ();
    return pow((pow((x1 - x0), 2) + pow((y1 - y0), 2) + pow((z1 - z0), 2)), 0.5);

}



void Ray_tracing(const map<string, vector<double>>* params, const map<string, int>* screen, const vector< Figure* >* figrs)
{
    int height = screen->find("height")->second, width = screen->find("width")->second;
    double dist = params->find("screen")->second.at(0), angle = params->find("alpha")->second.at(0),\
        pixel_side, pixel_diag, rlwidth, rlheight;
    Point cam(params->find("cam")->second.at(0), params->find("cam")->second.at(1), params->find("cam")->second.at(2));
    vector<double> norm = params->find("normal")->second, up = params->find("up")->second, aside, startV, toCent,\
        light = params->find("light")->second;
    if(tan(angle * PI / 380) == 0)//180
        throw std::invalid_argument("Error! tan(angle) = 0");
    if(dist == 0)
        throw std::invalid_argument("Error! screen = 0");
    if(width == 0 )
        throw std::invalid_argument("Error! width = 0");
    if (height == 0)
        throw std::invalid_argument("Error! height = 0");
    Normalize("vect", up);
    Normalize("vect", norm);
    rlheight = 2 * dist * tan(angle * PI / 360); //180
    pixel_side = rlheight / height;
    pixel_diag = pixel_side * pow(2, 0.5); // side*sqrt(2)
    rlwidth = pixel_side * static_cast<double>(width);
    aside = cross(up, norm);
    //aside = cross(norm, up);
    Normalize("vect", aside);
    toCent.push_back(norm.at(0) * dist);
    toCent.push_back(norm.at(1) * dist);
    toCent.push_back(norm.at(2) * dist);
    Point CenterOfScreen(toCent.at(0) + cam.getX(), toCent.at(1) + cam.getY(), toCent.at(2) + cam.getZ());
    Point LeftBottom((CenterOfScreen.getX() - aside.at(0)*rlwidth / 2 - up.at(0)* rlheight / 2),\
        (CenterOfScreen.getY() - aside.at(1) * rlwidth / 2 - up.at(1) * rlheight / 2),\
        CenterOfScreen.getZ() - aside.at(2) * rlwidth / 2 - up.at(2) * rlheight / 2);
    //Point CenterOfScreen(toCent.at(0) + cam.getX(), toCent.at(1) + cam.getY(), toCent.at(2) + cam.getZ());
    //Point LeftBottom((CenterOfScreen.getX() - rlwidth / 2), \
        //(CenterOfScreen.getY() - rlheight / 2), CenterOfScreen.getZ());
    
    //curVect.at(0) = startV.at(0) + i * pixel_side * up.at(0) + j * pixel_side * aside.at(0);
    //startV.resize(3);
    /* startV.at(0) = up.at(0) * (rlHeight - pixel_side) / 2 + aside.at(0) * pixel_side / 2 * (static_cast<double>(width) - 1) + toCent.at(0);
    startV.at(1) = up.at(1) * (rlHeight - pixel_side) / 2 + aside.at(1) * pixel_side / 2 * (static_cast<double>(width) - 1) + toCent.at(1);
    startV.at(2) = up.at(2) * (rlHeight - pixel_side) / 2 + aside.at(2) * pixel_side / 2 * (static_cast<double>(width) - 1) + toCent.at(2);*/
    //Normalize("vect", startV);
    double leftbotPix_x, leftbotPix_y, leftbotPix_z;
    leftbotPix_x = LeftBottom.getX() + 0.5 * up.at(0) * pixel_side + 0.5 * aside.at(0) * pixel_side;
    leftbotPix_y = LeftBottom.getY() + 0.5 * up.at(1) * pixel_side + 0.5 * aside.at(1) * pixel_side;
    leftbotPix_z = LeftBottom.getZ() + 0.5 * up.at(2) * pixel_side + 0.5 * aside.at(2) * pixel_side;
    startV.push_back(leftbotPix_x - cam.getX());
    startV.push_back(leftbotPix_y - cam.getY());
    startV.push_back(leftbotPix_z - cam.getZ());
    Point leftbotPix(leftbotPix_x, leftbotPix_y, leftbotPix_z);
    /*startV.push_back( LeftBottom.getX() - cam.getX());
    startV.push_back(LeftBottom.getY() - cam.getY());
    startV.push_back(LeftBottom.getZ() - cam.getZ());*/
    Normalize("vect", startV);
    /*startV.push_back(norm.at(0) * dist);
    startV.push_back(norm.at(1) * dist);
    startV.push_back(norm.at(2) * dist);*/
    cimg_library::CImg<unsigned char> img(width, height, 1, 3);
    img.fill(0);
    unsigned char white[] = { 255,255,255 }, red[] = { 255,0,0 };
    img.draw_text(100, 100, "Hello World", white);
    //img.display("My first CImg code");
    cout << "before loop" << endl;
    /*for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           
                img.draw_point(i, j, white);

        }
    }*/
    //double side = (dist * tan(asin(1) * 2 * angle / 360)) / static_cast<double>(height) / 2;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    //#pragma omp parallel for
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            vector<double> curVect;
            //Ray curRay;
            curVect.resize(3);
            /*curVect.at(0) = startV.at(0) - i * pixel_side * up.at(0) - j * pixel_side * aside.at(0);
            curVect.at(1) = startV.at(1) - i * pixel_side * up.at(1) - j * pixel_side * aside.at(1);
            curVect.at(2) = startV.at(2) - i * pixel_side * up.at(2) - j * pixel_side * aside.at(2);*/

            /*curVect.at(0) = startV.at(0) + (static_cast<double>(height) / 2 - i) * side * up.at(0) + (static_cast<double>(width) / 2 - j) * side * aside.at(0);
            curVect.at(1) = startV.at(1) + (static_cast<double>(height) / 2 - i) * side * up.at(1) + (static_cast<double>(width) / 2 - j) * side * aside.at(1);
            curVect.at(2) = startV.at(2) + (static_cast<double>(height) / 2 - i) * side * up.at(2) + (static_cast<double>(width) / 2 - j) * side * aside.at(2);
            */
            Point curP(leftbotPix_x + i * pixel_side * up.at(0) + j * pixel_side * aside.at(0),\
                leftbotPix_y + i * pixel_side * up.at(1) + j * pixel_side * aside.at(1),\
                leftbotPix_z + i * pixel_side * up.at(2) + j * pixel_side * aside.at(2));

            /*curVect.at(0) = startV.at(0) + i * pixel_side * up.at(0) + j * pixel_side * aside.at(0);
            curVect.at(1) = startV.at(1) + i * pixel_side * up.at(1) + j * pixel_side * aside.at(1);
            curVect.at(2) = startV.at(2) + i * pixel_side * up.at(2) + j * pixel_side * aside.at(2);*/
            curVect.at(0) = curP.getX() - cam.getX();
            curVect.at(1) = curP.getY() - cam.getY();
            curVect.at(2) = curP.getZ() - cam.getZ();
            Normalize("vect", curVect);

            //Normalize("vect", curVect);
            //cout << "curvect " << curVect.at(0) <<" "<< curVect.at(1) << " " << curVect.at(2) << endl;
            //cout << dot(curVect, curVect) << endl;
            vector<vector<double>> res;
            vector<double> pnt;
            /*if (figrs->at(0)->intersect(&Ray(curVect, cam), res)) {
               //img.draw_point(i, j, white);
                unsigned char color[] = { figrs->at(0)->get_Red(), figrs->at(0)->get_Green(), figrs->at(0)->get_Blue() };
                img.draw_point(i, j, red);
                //img.draw_point(i, j, color);
                //cout << i << j << endl;
            }*/
            
            vector< Figure* > intersectedFigrs;
            int len = figrs->size(), min_ind = 0;
            for (int k = 0; k < len; k++) {
                if (figrs->at(k)->intersect(Ray(curVect, cam), pnt)) {
                    intersectedFigrs.push_back(figrs->at(k));
                    res.push_back(pnt);
                }
            }
            //cout << "size = " << intersectedFigrs.size() << endl;
            if (intersectedFigrs.size() == 0)
                continue;
            min_ind = TakeTheNearest(&intersectedFigrs, &cam);
            if(min_ind >= static_cast<int>(res.size()))
                throw std::invalid_argument("Error! min_ind >= res.size");
            Point inter(res.at(min_ind));
            //cout << intersectedFigrs.size() << " " << min_ind << " "<<res.size()<< endl;
            //sphere 200 0 0 30 0 -90 10
            //box 200 200 0 30 0 -90 70 10 -80
            RGB rgb(intersectedFigrs.at(min_ind)->get_ColorOfPoint(inter, light, cam));
            unsigned char color[] = { rgb.get_red(), rgb.get_green(), rgb.get_blue() };
            //unsigned char color[] = { intersectedFigrs.at(min_ind)->get_Red(), intersectedFigrs.at(min_ind)->get_Green(),\
              //intersectedFigrs.at(min_ind)->get_Blue() };
            img.draw_point(j, i, color);

            
        }
    }
    cout << "after loop" << endl;
    //img.draw_text(100, 100, "Hello World", white);
    img.save("img.bmp");
    //img.display();
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "function runtime is " << elapsed_ms << " ms\n";
    return;
}


/*void prov(map<string, vector<double>> *par)
{
    double k = par->find("cam")->second.at(0);
    std::cout << "EEE"<<k<<std::endl;
}*/


/*Figure* Create_Figure(list<string>& words)
{
    list<string> ::iterator it = words.begin(), last = words.end();
    if (it == last) {
        throw std::invalid_argument("Error! Empty data");
    }
    vector <double> coord;
    last--;
    last--;
    last--;
    while (it != last) { coord.push_back(atof((*it).c_str())); it++; }
    last = words.end();
    if (*words.begin() == "sphere")
    {
        cout << "Sp" << endl;
        if (words.size() != 8) {
            throw std::invalid_argument("Error! Wrong data");
        }
        while (it != last) { cout << *it << endl; it++; }
        it = words.begin();
        last = words.end();
        return new Sphere(atof((*(it++)).c_str()), atof((*(it++)).c_str()), \
            atof((*(it++)).c_str()), atof((*(it++)).c_str()), \
            atoi((*(it++)).c_str()), atoi((*(it++)).c_str()), atoi((*(it++)).c_str()));

    }
    if (*words.begin() == "box")
    {
        cout << "B" << endl;
        if (words.size() != 10) {
            throw std::invalid_argument("Error! Wrong data");
        }
    }
    else if (*words.begin() == "tetra")
    {
        cout << "T" << endl;
        if (words.size() != 16) {
            throw std::invalid_argument("Error! Wrong data");
        }
    }
    return NULL;

}*/
