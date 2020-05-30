#pragma once
#include <iostream>
#include <vector>
class Point{
    double X, Y, Z;
    public:
        Point() { X = 0; Y = 0; Z = 0; };
        Point(const double x0, const double y0, const double z0) { X = x0; Y = y0; Z = z0; };
        Point(const std::vector<double>& vect) { 
            if(vect.size() != 3) throw std::invalid_argument("Error! vect.size in point constructor");
            X = vect.at(0);
            Y = vect.at(1);
            Z = vect.at(2);
        };
        Point(const Point& other) { X = other.X; Y = other.Y; Z = other.Z; };
        ~Point() {};
        double getX() const { return X; };
        double getY() const { return Y; };
        double getZ() const { return Z; };
        Point& operator=(const Point& other) {
            X = other.X;
            Y = other.Y;
            Z = other.Z;
            return *this;
        }
};
