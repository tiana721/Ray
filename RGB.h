#pragma once
#include<iostream>
class RGB {
    unsigned char   rgbBlue;
    unsigned char   rgbGreen;
    unsigned char   rgbRed;
public:
    RGB() { rgbRed = 0; rgbGreen = 0; rgbBlue = 0; }
    RGB(const unsigned char red, const unsigned char green, const unsigned char blue) {
        //if(((red > 255)||(red < 0)) || ((blue > 255) || (blue < 0)) || ((green > 255) || (green < 0)))
            //throw std::invalid_argument("Error! Wrong color");
        rgbRed = red;
        rgbGreen = green;
        rgbBlue = blue;
    }
    RGB(const int red, const int green, const int blue) {
        //if(((red > 255)||(red < 0)) || ((blue > 255) || (blue < 0)) || ((green > 255) || (green < 0)))
          //  throw std::invalid_argument("Error! Wrong color");
        rgbRed = red;
        rgbGreen = green;
        rgbBlue = blue;
    }
    RGB& operator=(const RGB& other) {
        rgbBlue = other.rgbBlue;
        rgbGreen = other.rgbGreen;
        rgbRed = other.rgbRed;
        return *this;
    }
    void set_blue(const unsigned char blue) { rgbBlue = blue; }
    void set_red(const unsigned char red) { rgbRed = red; }
    void set_green(const unsigned char green) { rgbGreen = green; }
    unsigned char get_red() const { return rgbRed; }
    unsigned char get_blue() const { return rgbBlue; }
    unsigned char get_green() const { return rgbGreen; }
    ~RGB() {};
    //int   rgbReserved;
};