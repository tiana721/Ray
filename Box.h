#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED
#include <vector>
#include <stdexcept>
#include"Figure.h"
class Box : public Figure{
    double maxVert[3], minVert[3];
    public:
           Box() : Figure()
           {
               maxVert[0] = 0;
               maxVert[1] = 0;
               maxVert[2] = 0;
               minVert[0] = 0;
               minVert[1] = 0;
               minVert[2] = 0;
           }
           Box(const RGB color) : Figure(color) 
           {
               maxVert[0] = 0;
               maxVert[1] = 0;
               maxVert[2] = 0;
               minVert[0] = 0;
               minVert[1] = 0;
               minVert[2] = 0;
           };
           Box(const std::vector<double>& coord, const unsigned char red, const unsigned char green,\
           const unsigned char blue) : Figure(red, green, blue)
           {
               if(coord.size() != 6)
                   throw std::invalid_argument("Error! Coord_Len != 6");
               if(coord.at(2) >= coord.at(5))
                   throw std::invalid_argument("Error! minVert >= maxVert");
               minVert[0] = coord.at(0);
               minVert[1] = coord.at(1);
               minVert[2] = coord.at(2);
               maxVert[0] = coord.at(3);
               maxVert[1] = coord.at(4);
               maxVert[2] = coord.at(5);
           }
           Box(const RGB color, const std::vector<double>& coord) : Figure(color)
           {
               if (coord.size() != 6)
                   throw std::invalid_argument("Error! Coord_Len != 6");
               if (coord.at(2) >= coord.at(5))
                   throw std::invalid_argument("Error! minVert >= maxVert");
               minVert[0] = coord.at(0);
               minVert[1] = coord.at(1);
               minVert[2] = coord.at(2);
               maxVert[0] = coord.at(3);
               maxVert[1] = coord.at(4);
               maxVert[2] = coord.at(5);
           }
           Point get_Center() const;
           std::vector<double> min_vert() const;
           std::vector<double> max_vert() const;
           void set_minV(const double x, const double y, const double z);
           void set_maxV(const double x, const double y, const double z);
           void print() const;
           int intersect(const Ray& ray, std::vector<double>& point) const;
           RGB get_ColorOfPoint(const Point inter, const std::vector<double>& light, const Point cam) const;
           ~Box(){};
};

#endif // BOX_H_INCLUDED
