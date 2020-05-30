#pragma once
#include "factory.h"
//#include<iostream>
#include "Figure.h"
#include "Tetra.h"
class FactoryTetra : public Factory {
public:
    Figure* Create(const RGB color, const std::vector<double>& data) const {
        return new Tetra(color, data);
    }
    FactoryTetra() :Factory() {};
    ~FactoryTetra() {};
};