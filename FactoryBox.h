#pragma once
#include "factory.h"
//#include<iostream>
#include "Figure.h"
#include "Box.h"
class FactoryBox : public Factory {
public:
    Figure* Create(const RGB color, const std::vector<double>& data) const {
        return new Box(color, data);
    }
    FactoryBox() :Factory() {};
    ~FactoryBox() {};
};