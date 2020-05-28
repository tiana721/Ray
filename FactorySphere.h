#pragma once
#include "factory.h"
//#include<iostream>
#include "Figure.h"
#include "Sphere.h"
class FactorySphere : public Factory {
public:
    Figure* Create(const RGB color, const std::vector<double>& data) const {
        return new Sphere(color, data);
    }
    FactorySphere() :Factory() {};
    ~FactorySphere() {};
};