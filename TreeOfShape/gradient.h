#ifndef GRADIENT_H
#define GRADIENT_H

#include "Common/Image.h"
#include <math.h>

using namespace LibTIM;

using type_pixels = LibTIM::U8;
class Gradient
{
public:
    Gradient(){}

    Image<type_pixels> Sobel(const Image<type_pixels>& img);
};


#endif // GRADIENT_H
