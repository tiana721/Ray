#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "Figure.h"
#include "Point.h"
using namespace std;

void Check_lenParam(const string& Type, const size_t size);
void Check_CntParams(const map<string, vector<double>> *params);
void Check_Screen(const map<string, int>* screen);
void Normalize(const string& Type, vector<double>& vect);
double dot(const vector<double>& a, const vector<double>& b);
void Ray_tracing(const map<string, vector<double>>* params, const map<string, int>* screen, const vector< Figure* >* figrs);
vector<double> cross(const vector<double>& a, const vector<double>& b);
double max(const double a, const double b);
double min(const double a, const double b);
double triangle_square(double a, double b, double c);
//int inside_triangle(double P_x, double P_y, double P_z, double A_x, double A_y, double A_z, double B_x, double B_y, double B_z,\
    //double C_x, double C_y, double C_z);
int inside_triangle(double P_x, double P_y, double P_z, vector<double>& A, vector<double>& B, vector<double>& C);
bool is_equal(double x, double y);
double get_dist(const Point* pnt1, const Point* pnt2);
int TakeTheNearest(const vector< Figure* >* figrs, const Point* cam);
double triangle_intersect(const Ray& ray, const vector<double>& v0, const vector<double>& v1, const vector<double>& v2);
//void prov(map<string, vector<double>> *par);
//int IsNotInTheArea(Figure* figure, map < string, vector<double> >& params);
//void Ray_tracing(map < string, vector<double> > parameters, const size_t size);
//Figure* Create_Figure(list<string>& words);