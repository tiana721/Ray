#pragma once
#include <iostream>
#include <vector>
#include "Figure.h"

class Factory {
public:
    virtual Figure* Create(const RGB color, const std::vector<double>& data) const = 0;

    Factory() {};
    virtual ~Factory() {};
};