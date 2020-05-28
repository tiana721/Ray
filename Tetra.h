#ifndef TETRA_H_INCLUDED
#define TETRA_H_INCLUDED
#include <iostream>
#include <vector>
#include <stdexcept>
#include"Figure.h"
class Tetra : public Figure{
    std::vector<double> vertex;
    public:
        Tetra(const RGB color) : Figure(color) {};
        Tetra(const RGB color, const std::vector<double>& data) : Figure(color)
        {
            if (data.size() != 12)
                throw std::invalid_argument("Error! vertex_Len != 12");
            for (int i = 0; i < 12; i++)
                vertex.push_back(data.at(i));
        };
        Tetra(const std::vector<double>& vect, const unsigned char red, const unsigned char green,\
           const unsigned char blue) : Figure(red, green, blue)
        {
               if(vect.size() != 12)
                   throw std::invalid_argument("Error! vertex_Len != 12");
               for(int i = 0; i < 12; i++)
                     vertex.push_back(vect.at(i));
        }
        void set_val(const double num);
        std::vector<double> get_vert1() const;
        std::vector<double> get_vert2() const;
        std::vector<double> get_vert3() const;
        std::vector<double> get_vert4() const;
        int intersect(const Ray& ray, std::vector<double>& point) const;
        vector<int> getSurfwithPnt(const Ray& ray) const;
        RGB get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const;
        Point get_Center() const;
        void print() const;
        ~Tetra(){};
};

#endif // TETRA_H_INCLUDED
